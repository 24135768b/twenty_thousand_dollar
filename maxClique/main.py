import networkx as nx
from tqdm import tqdm
import matplotlib.pyplot as plt
# ---- Setting ----
DEV = True
TestCase = "../test.in" if DEV else "../input.txt"

if __name__ == "__main__":
    G = nx.Graph()
    with open(TestCase) as f:
        lines = f.readlines()
        for line in tqdm(lines):
            line = line.replace("\t", " ").replace(
                "  ", " ").replace("\n", "").lstrip()
            i, j, w = line.split(" ")[:3]
            i = int(i)
            j = int(j)
            G.add_edge(i, j, weight=w)
    result = nx.make_max_clique_graph(G)

    nx.draw_networkx(result)
    plt.savefig("filename.png")
