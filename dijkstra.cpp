    using pii = pair<int, int>;
    vector<pii> graph[MAXN];
    vector<int> dis(MAXN, 1e9 + 7);
    void dijkstra(int src){
        priority_queue<pii, vector<pii>, greater<pii> > pq;
        pq.push({0, src});
        // pair = weght, destination
        dis[src] = 0;
        while(!pq.empty()){
            int from = pq.top().second, d = pq.top().first;
            pq.pop();
            if(dis[from] < d) continue;
            for(auto& [wt, to] : graph[from]){
                if(wt + dis[from] < dis[to])
                        dis[to] = wt + dis[from],
                        pq.push({dis[to], to});
            }
        }
    }
