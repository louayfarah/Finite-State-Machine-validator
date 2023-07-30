//Louay Farah
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define pb push_back
#define mp make_pair
#define endl "\n"
#define fi first
#define se second
 
const int nx[4] = {0, 0, 1, -1};
const int ny[4] = {1, -1, 0, 0};
 
//Disjoint Set Union implementation
//This data structure will be used to check whether some states are disjoint or not
struct dsu
{
    vector<int> link;
    vector<int> len;
    ll comps;
 
    void init(int n)
    {
        link.assign(n+1, 0);
        len.assign(n+1, 0);
 
        for(int i = 1; i<=n; i++)
        {
            link[i] = i;
            len[i] = 1;
        }
 
        comps = n;
    }
 
    //Find the representative of u
    int find(int u)
    {
        if(u!=link[u])
            link[u] = find(link[u]);
        return link[u];
    }
 
    //check whether u and v have the same representative or not
    bool check(int u, int v)
    {
        return find(u)==find(v);
    }
 
    //Unite two nodes u and v
    void unite(int u, int v)
    {
        u = find(u);
        v = find(v);
 
        if(u==v)
            return;
 
        comps--;
        if(len[u]<len[v])
            swap(u, v);
        len[u]+=len[v];
        link[v] = u;
    }
};
 
 
//Function to check whether a state is valid or not (consists only of numbers and latin letters)
bool state_is_valid(string state)
{
    for(auto c: state)
    {
        if(!((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9')))
            return false;
    }
 
    return true;
}
 
//Function to check whether an alphabet element is valid or not (consists only of numbers, latin letters, and undersocore '_')
bool name_is_valid(string name)
{
    for(auto c: name)
    {
        if(!((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9')||(c == '_')))
            return false;
    }
 
    return true;
}
 
//Depth-first search algorithm to check whether all the states are reachable from the initial state or not
void dfs(vector<pair<ll, string>> adj[], ll u, vector<bool> &visited)
{
    if(visited[u])
        return ;
    visited[u] = true;
 
    for(auto v: adj[u])
    {
        dfs(adj, v.fi, visited);
    }
}
 
int main()
{
    freopen("fsa.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
 
    //BSTs to check the inclusivity of s/a
    set<string> states, alphabet;
    //Dynamic arrays to store the initial state and final states
    vector<string> initial_state, final_states;
    //To store the transitions: s1>a>s2 becomes mp(mp(s1, s2), a)
    vector<pair<pair<string, string>, string>> transitions;
 
    //input states
    string s;
    cin >> s;
 
    //extract states
    ll i = 8;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        states.insert(curr);
        i++;
    }
 
    for(auto state: states)
    {
        if(!state_is_valid(state))
        {
            cout << "Error:" << endl;
            cout << "E5: Input file is malformed" << endl;
            return 0;
        }
    }
 
    //input alpha
    cin >> s;
 
    //extract alpha
    i = 7;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        alphabet.insert(curr);
        i++;
    }
 
    for(auto name: alphabet)
    {
        if(!name_is_valid(name))
        {
            cout << "Error:" << endl;
            cout << "E5: Input file is malformed" << endl;
            return 0;
        }
    }
 
    //input initial state(s)
    cin >> s;
 
    //extract initial state(s)
    i = 9;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        initial_state.pb(curr);
        i++;
    }
 
    //input final state(s)
    cin >> s;
 
    //extract final state(s)
    i = 8;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        final_states.pb(curr);
        i++;
    }
 
 
    for(auto state: final_states)
    {
        if(states.count(state) == 0) //If the curr final state doesn't belong to states
        {
            cout << "Error:" << endl;
            cout << "E1: A state '" << state << "' is not in the set of states" << endl;
            return 0;
        }
    }
 
    if(int(initial_state.size()) > 1) //If more than one initial state
    {
        cout << "Error:" << endl;
        cout << "E5: Input file is malformed" << endl;
        return 0;
    }
 
    if(initial_state.empty()) //If no initial states
    {
        cout << "Error:" << endl;
        cout << "E4: Initial state is not defined" << endl;
        return 0;
    }
 
    if(states.count(initial_state[0]) == 0) //If the initial state doesn't belong to states
    {
        cout << "Error:" << endl;
        cout << "E1: A state '" << initial_state[0] << "' is not in the set of states" << endl;
        return 0;
    }
 
    //input transitions
    cin >> s;
 
    //extract transitions
    i = 7;
    while(i < int(s.length())-1)
    {
        string a = "", b = "", w = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == '>')
                break;
            a.pb(s[i]);
            i++;
        }
        i++;
 
        while(i < int(s.length())-1)
        {
            if(s[i] == '>')
                break;
            w.pb(s[i]);
            i++;
        }
        i++;
 
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            b.pb(s[i]);
            i++;
        }
        i++;
 
        if(states.count(a) == 0)
        {
            cout << "Error:" << endl;
            cout << "E1: A state '" << a << "' is not in the set of states" << endl;
            return 0;
        }
 
        if(states.count(b) == 0)
        {
            cout << "Error:" << endl;
            cout << "E1: A state '" << b << "' is not in the set of states" << endl;
            return 0;
        }
 
        if(alphabet.count(w) == 0)
        {
            cout << "Error:" << endl;
            cout << "E3: A transition '" << w << "' is not represented in the alphabet" << endl;
            return 0;
        }
 
        transitions.pb(mp(mp(a, b), w));
    }
 
    dsu d;
    d.init(int(states.size()));
 
    //Hash every state to a unique number for usage in dsu / dfs
    map<string, ll> m;
    ll counter = 1;
    for(auto state: states)
    {
        m[state] = counter++;
    }
 
    ll nb_states = int(states.size());
 
    //Adjacency matrix for dfs
    vector<pair<ll, string>> adj[nb_states+1];
 
    //Build the adjacency matrix
    for(auto p: transitions)
    {
        adj[m[p.fi.fi]].pb(mp(m[p.fi.se], p.se));
    }
 
    //unite the states
    for(int u = 1; u<=nb_states; u++)
    {
        for(auto v: adj[u])
        {
            d.unite(u, v.fi);
        }
    }
 
    if(d.comps != 1) //If some states are disjoint
    {
        cout << "Error:" << endl;
        cout << "E2: Some states are disjoint" << endl;
        return 0;
    }
 
    //Set to store unique transitions. i.e. if the fsa is non-deterministic
    set<pair<string, string>> unique_transitions;
    for(auto p: transitions)
    {
        unique_transitions.insert(mp(p.fi.fi, p.se));
    }
 
    if(int(unique_transitions.size()) == nb_states * int(alphabet.size()))
    {
        cout << "FSA is complete" << endl;
    }
    else
    {
        cout << "FSA is incomplete" << endl;
    }
 
    vector<int> warnings;
 
    if(final_states.empty()) //If there are no final states
    {
        warnings.pb(1);
    }
 
    vector<bool> visited(nb_states+1, false);
    dfs(adj, m[initial_state[0]], visited);
    for(int i = 1; i<=nb_states; i++)
    {
        if(!visited[i]) //If state with index i is not reachable from the initial state
        {
            warnings.pb(2);
            break;
        }
    }
 
    if(unique_transitions.size() != transitions.size()) //If the fsa is non-deterministic
    {
        warnings.pb(3);
    }
 
    if(!warnings.empty())
    {
        cout << "Warning:" << endl;
        for(auto w: warnings)
        {
            if(w == 1)
            {
                cout << "W1: Accepting state is not defined" << endl;
            }
            else if(w == 2)
            {
                cout << "W2: Some states are not reachable from the initial state" << endl;
            }
            else if(w == 3)
            {
                cout << "W3: FSA is nondeterministic" << endl;
            }
        }
    }
 
    return 0;
}
