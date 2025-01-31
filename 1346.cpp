#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1000005;
const ll INF = 0x7FFF'FFFF'FFFF'FFFF;
ll n, k, p, init_val[N], val[N << 2], lazy_tag[N << 2];
void push_up(ll rt)
{
    val[rt] = min(val[rt * 2], val[rt * 2 + 1]);
}
void push_down(ll rt, ll l, ll r)
{
    if (lazy_tag[rt] != 0)
    {
        ll mid = (l + r) >> 1;
        lazy_tag[rt * 2] += lazy_tag[rt];
        lazy_tag[rt * 2 + 1] += lazy_tag[rt];
        val[rt * 2] += lazy_tag[rt];
        val[rt * 2 + 1] += lazy_tag[rt];
        lazy_tag[rt] = 0;
    }
}
void build(ll rt, ll l, ll r)
{
    if (l == r)
    {
        val[rt] = init_val[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    push_up(rt);
}
void update(ll nl, ll nr, ll l, ll r, ll rt, ll k)
{
    if (nl <= l && r <= nr)
    {
        val[rt] += k;
        lazy_tag[rt] += k;
        return;
    }
    push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, rt * 2, k);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rt * 2 + 1, k);
    push_up(rt);
}
ll query(ll qx, ll qy, ll l, ll r, ll rt)
{
    if (qx <= l && r <= qy)
        return val[rt];
    push_down(rt, l, r);
    ll mid = (l + r) >> 1;
    ll ans = INF;
    if (qx <= mid)
        ans = min(ans, query(qx, qy, l, mid, rt * 2));
    if (qy > mid)
        ans = min(ans, query(qx, qy, mid + 1, r, rt * 2 + 1));
    return ans;
}
int main()
{
    scanf("%lld%lld%lld", &n, &k, &p);
    k += p;
    while (k-- > 0)
    {
        ll op, a, b;
        scanf("%lld%lld%lld", &op, &a, &b);
        if (op == 1)
            update(a, b, 1, n, 1, 1);
        else
            printf("%lld\n", query(a, b, 1, n, 1));
    }
    return 0;
}
