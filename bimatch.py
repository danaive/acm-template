'''
Created on 2014-8-14

@author: dlWang
'''
import queue
def bfs():
    global dx, dy, cx, cy, n, mp
    tag = False
    q = queue.Queue(maxsize = 0)
    dx = []
    dy = []
    for i in range(n):
        dx.append(0)
        dy.append(0)
        if cx[i] == -1:
            q.put(i)
    while q.empty() == False:
        u = q.get()
        for v in mp[u]:
            if dy[v] == 0:
                dy[v] = dx[u] + 1
                if cy[v] == -1:
                    tag = True
                else:
                    dx[cy[v]] = dy[v] + 1
                    q.put(cy[v])
    return tag

def dfs(u):
    global dx, dy, cx, cy, n, mp
    for v in mp[u]:
        if dy[v] == dx[u] + 1:
            dy[v] = 0
            if cy[v] == -1 or dfs(cy[v]):
                cx[u] = v
                cy[v] = u
                return True;
    return False

def hk():
    global cx, cy, n
    match = 0
    cx = []
    cy = []
    for i in range(n):
        cx.append(-1)
        cy.append(-1)
    while bfs() == True:
        for i in range(n):
            if cx[i] == -1 and dfs(i):
                match += 1
    return match

ab = input().split()
n = int(input())
mp = []
a = []
b = []
for i in range(n):
    s = input().split()
    if s[1] == '0':
        a.append(int(s[0]))
    else:
        b.append(int(s[0]))
n = int(n / 2)
for i in range(n):
    mp.append([])
    for j in range(n):
        if b[j] - a[i] >= int(ab[0]) or 0 < b[j] - a[i] <= int(ab[1]):
            mp[i].append(j)
ans = hk()
if ans != n:
    print('Liar') 
else:
    print('No reason')
    for i in range(n):
        print(a[i], b[cx[i]])
            
            
            
            
            
            
            
            
            
            
            
            