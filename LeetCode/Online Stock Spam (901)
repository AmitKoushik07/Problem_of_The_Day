class StockSpanner 
{
public:
    vector<pair<int,int>> s;
    
    int next(int p) 
    {
        int c = 1;
        while (!s.empty() && s.back().first <= p)
            c += s.back().second, s.pop_back();
        s.emplace_back(p, c);
        return c;
    }
};
