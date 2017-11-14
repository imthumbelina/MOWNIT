import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

# wczytanie listy krawędzi oraz SEM
G = nx.read_edgelist("data.csv", delimiter=" ", data=[("weight", float)])
G = nx.relabel_nodes(G, lambda x: int(x))
(s, t, E) = np.genfromtxt('edge.csv', dtype=int, delimiter=' ')  # load SEM
nx.draw_networkx(G)
plt.show()

reference_node = s
voltage_node = t

#tworzymy macierz transmitancji M

num_of_nodes = len(G.nodes())
M = np.zeros((num_of_nodes,num_of_nodes))
print(M)

# wypelniamy macierz transmitancji M

for node in G.nodes():
    for neighbour in G.neighbors(node):
        M[node][node] += 1 / G[node][neighbour]['weight']
        M[node][neighbour] = - 1 / G[node][neighbour]['weight']

print(M)

#Dodanie wiersza i kolumny zwiazanych z wezlem, w ktorym potencjal jest znany dzieki
#podlaczeniu SEM do niego i do wezla odniesienia

new_row = np.zeros((M.shape[0]))
new_row[voltage_node] = -1
M = np.vstack((M, new_row ))

new_column = np.zeros((M.shape[0],1))
new_column[voltage_node] = 1
M = np.hstack((M, new_column))

print(M)

#usuniecie wiersza i kolumny zwiazanych z wezlem odniesienia

M = np.delete(M, reference_node, 0)
M = np.delete(M, reference_node, 1)

print(M)

#utworzenie wektora I

I = np.zeros(M.shape[1])
I[M.shape[1]-1] = E

# wyliczenie wektora potencjalow w wezlach V

V = np.linalg.solve(M,I)
print(V)

#dodanie zerowego potencjalu w reference node i usuniecie
#pradu w galezi z SEM

V = np.insert(V,reference_node, 0, axis = 0)
V = np.delete(V, V.shape[0] - 1, 0)

#macierz napiec miedzy wezlami

volt_matrix = np.zeros((num_of_nodes,num_of_nodes))
print(volt_matrix)

#wypelnienie macierzy napiec

for node in G.nodes():
    for j in range(node, num_of_nodes):
        volt_matrix[node][j] = V[node] - V[j]
        volt_matrix[j][node] = V[j] - V[node]

print(volt_matrix)

#dodanie wartosci natezen pradu w poszczegonych galeziach

for edge in G.edges():
    j = edge[0]
    k = edge[1]
    G[j][k]['current'] = volt_matrix[j][k] / G[j][k]['weight']

# drukowanie

for edge in G.edges():
    print(edge, G[edge[0]][edge[1]]['current'])
