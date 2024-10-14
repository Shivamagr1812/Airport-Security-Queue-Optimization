#include <bits/stdc++.h>
#include <iostream> 
#include <chrono> 
#include <thread> 
#include <random> 
using namespace std; 

int PacketDropped;
 
struct packet{
    double arrival;
    double departure;
    double serviceTime;

    packet()
    {
        arrival=0;
        departure=0;
        serviceTime=-1;
    }
};

struct server
{
    deque<packet*> q;
    int size;
    exponential_distribution<double> distribution; 
    default_random_engine generator;
    double prev, total,summation,utilisation,avgQueueSize,lambda;
    priority_queue <pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>> > pq;

    server(int m,double n)
    {
        q.clear();
        size = m;
        lambda = n;
        distribution.param(std::exponential_distribution<double>::param_type(lambda));
        prev =0;
        total=0;
        summation=0;
        utilisation=0;
    }

    void randomise(int j)
    {
        generator.seed(int(chrono::system_clock::now().time_since_epoch().count())+j);
    }

    int currsize()
    {
        return q.size();
    }

    double enquePacket(packet * p )
    {
        if(q.size()>=size)
        {
            p->departure=-1;
            PacketDropped++;
            return -1;
        }
        total+=p->arrival-prev;
        if(q.size()!=0)
        utilisation+=p->arrival-prev;
        summation+=double(q.size())*(p->arrival-prev);
        prev= p->arrival;
        if(!q.empty())
        {
            p->departure = q.back()->departure+ distribution(generator);
            // cout<<"Service Time = "<<p->departure-q.back()->departure<<endl;
            p->serviceTime=p->departure-q.back()->departure;
        }
        else
        {
            p->departure = p->arrival + distribution(generator);
            // cout<<"Service Time = "<<p->departure-p->arrival<<endl;
            p->serviceTime= p->departure-p->arrival;
        }
        
        q.push_back(p);
        return p->departure;
    }

    void dequePacket()
    {
        total+=q.front()->departure-prev;
        utilisation+=q.front()->departure-prev;
        summation+=double(q.size())*(q.front()->departure-prev);
        prev= q.front()->departure;
        q.pop_front();
    }

    void CalAvgQueue(double maxTot)
    {
        while (!q.empty())
        {
            dequePacket();
        }
        avgQueueSize=summation/maxTot;
        utilisation=(utilisation/maxTot)*100;
    }

};

void simulate(vector<server>& Servers,vector<packet>& Packets,double& avgWaiting, double& avgQueueSize, double& utilisation)
{
    priority_queue <pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>> > pq;
    int i =0;
    while (i<Packets.size())
    {
        if(pq.empty()||Packets[i].arrival<pq.top().first)
        {
            int index =-1, length=INT_MAX; 
            for (int j = 0; j < Servers.size(); j++)
            {
                if(Servers[j].currsize()<length)
                {
                    index=j;
                    length = Servers[j].currsize();
                }
            }
            // cout<<"Packet "<<i<<" Enqued at Server "<<index<<endl;
            pq.push({Servers[index].enquePacket(&Packets[i]),index});
            if(pq.top().first==-1)
            {
                // cout<<"Packet dropped due to insufficient Buffer"<<endl;
                PacketDropped++;
            }
            i++;
        }
        else
        {
            int index = pq.top().second;
            if(pq.top().first>0)
            {
                // cout<<"Job finished at Server "<<index<<endl;
                Servers[index].dequePacket();
            }
            pq.pop();
        }
    }
    while (!pq.empty())
    {
         int index = pq.top().second;
            if(pq.top().first>0)
            {
                // cout<<"Job finished at Server "<<index<<endl;
                Servers[index].dequePacket();
            }
            pq.pop();
    }
    double maxTot =0;
    for(int i =0;i<Servers.size();i++)
    {
        maxTot = max(maxTot,Servers[i].total);
    }
    for(int i =0;i<Servers.size();i++)
    {
        Servers[i].CalAvgQueue(maxTot);
        avgQueueSize+=Servers[i].avgQueueSize;
        utilisation+=Servers[i].utilisation;
    }

    avgQueueSize/=Servers.size();
    utilisation/=Servers.size();

    double avg=0;
    int total=0;
    for(auto x:Packets)
    {
        if(x.departure!=-1)
        {
            avg+=x.departure-x.arrival-x.serviceTime;
            total++;
        }
    }
    avgWaiting=avg/double(total);
}


void airport_queue_simulation(int n, int s, int b, double l, double w) 
{ 
    PacketDropped = 0;
    int seed = 
        chrono::system_clock::now().time_since_epoch().count(); 
    default_random_engine generator (seed); 
    
    exponential_distribution<double> distribution (w); 

    vector<server>  Servers(s,{b,l});
    for(int i=0;i<s;i++)
    {
        Servers[i].randomise(i);
    }
    vector<packet> v(n);
    double prev =0;
    for (int i=0; i<n; ++i) 
    {	 
        v[i].arrival = distribution(generator)+prev;
        prev=v[i].arrival; 
    }
    double avgWaiting=0; 
    double avgQueueSize=0;
    double utilisation=0;

    simulate(Servers,v,avgWaiting,avgQueueSize,utilisation);

    ofstream myfile;
    myfile.open("result.csv",ios::app);
    myfile<<n<<","<<s<<","<<b<<","<<l<<","<<w<<","<<PacketDropped<<","<<avgWaiting<<","<<avgQueueSize<<","<<utilisation<<endl;
    myfile.close();
}

int main() 
{
    int n = 100000;
    int s = 2;
    int b = 2;
    double l = 100;
    double w = 105;

    ofstream myfile;
    myfile.open("result.csv",ios::app);
    myfile<<"population_size,num_server,buffer_size,lambda,mu,num_dropped,avg_wait_time,avg_queue_length,server_util"<<endl;
    myfile.close();

    // Single server
    for(int i=0;i<100;i++)
    {
        s = 1;
        b = i+1;

        airport_queue_simulation(n,s,b,l,w);
    }

    // Multiple server
    for(int i=0;i<100;i++)
    {
        s = i+1;
        b = 2;

        airport_queue_simulation(n,s,b,l,w);
    }

    for(int i=0;i<100;i++)
    {
        s = 2;
        b = i+1;

        airport_queue_simulation(n,s,b,l,w);
    }

    return 0; 
}