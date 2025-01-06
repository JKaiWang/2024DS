#include <stdio.h>
long long ans = 0, e[501][501], u[501], mn[501];
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++) {
        long long u,v,w;
        scanf("%lld %lld %lld", &u, &v, &w);
        e[u][v] = e[v][u] = w;
    }

    for(int i=1;i<=n;i++) {
        mn[i] = 1e10;
    }

    long long now = 1, ans = 0;
    for(int i=0;i<n;i++) {
        u[now] = 2;
        for(int j=1;j<=n;j++) {
            if( e[now][j] != 0 && u[j] != 2 ) {
                u[j] = 1;
                if( mn[j] > e[now][j] ) mn[j] = e[now][j];
            }
        }

        long long pos = -1, mn_val = 1e10;
        for(int i=1;i<=n;i++) {
            if( u[i] != 2 && mn_val > mn[i] ) {
                mn_val = mn[i];
                pos = i;
            }
        }
        if( pos != -1 ) ans += mn_val;
        now = pos;
    }

    printf("%lld\n", ans);
}
