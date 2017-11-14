import networkx as nx
import numpy as np
import matplotlib.pyplot as plt


G = nx.read_edgelist("data.csv", delimiter=" ", data=[("weight", float)])
G = nx.relabel_nodes(G, lambda x: int(x))  # relabel nodes to be integers
(s,t, E) = np.genfromtxt("edge.csv",dtype = int, delimiter= " ")
G.add_edge(s, t, weight=0)
nx.draw_networkx(G)

plt.show()
print(s,t,E)

print(G.nodes());
print(G.edges());

#equations from 1 st Kirchoff's law
#we assume that current goes from node with lower number to node
#with higher number

K = np.zeros((len(G.nodes),len(G.edges)))


i = 0
for edge in G.edges():
    starting = min(edge[0],edge[1])
    ending = max(edge[0],edge[1])
    K[starting][i] = 1
    K[ending][i] = -1
    G[edge[0]][edge[1]]['current_label'] = i
    i+= 1

print(K)



def contains_SEM_edge(cycle):
    for i in range(len(cycle)-1):
        if((cycle[i]==s and cycle[i+1] == t) or (cycle[i]==t and cycle[i+1]==s)):
            return True
    if(cycle[0] == s and cycle[-1]==t):
        return True
    return False

def get_current(a,b):
    return G[a][b]['current_label']

def get_weight(a,b):
    return G[a][b]['weight']

K = K[1:]

i = K.shape[0] - 1

cycles = nx.cycle_basis(G)

U = np.zeros((len(G.edges),1 ))

for cycle in cycles:
    row = np.zeros((1,K.shape[1]))
    if contains_SEM_edge(cycle):
        U[i+1][0] = E
    for j in range(0,len(cycle)):
        if j == len(cycle) - 1:
            column = get_current(cycle[j],cycle[0])
            row[0][column] = get_weight(cycle[j],cycle[0])
        else:
            column = get_current(cycle[j],cycle[(j+1)])
            row[0][column] = get_weight(cycle[j],cycle[j+1])
    i+=1
    K = np.concatenate((K, row), axis = 0)
    if i == K.shape[1]:
        break

print(K)
print(U)

print(np.linalg.solve(K, U))
