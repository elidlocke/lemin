# libraries
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Colors
bg_color = '#111111'
line_color = '#282828'
default_node_color = '#0C6CFC'
se_node_color = '#0C6CFC'
highlight_color = '#FC9C0C'
# v modify to be 50% of highlight on white and back bg
odd_ant_color = "#8E590A"
even_ant_color = '#FDBA55'


#Input Data
node_names = ['START', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'END']
input_tunnels = [('START', 'A'),
                  ('A', 'B'),
                  ('B', 'END'),
                  ('START','C'),
                  ('C','D'),
                  ('D', 'END'),
                  ('START','E'),
                  ('E', 'F'),
                  ('F', 'G'),
                  ('G', 'H'),
                  ('H', 'I'),
                  ('I', 'J'),
                  ('I', 'K'),
                  ('J', 'K'),
                  ('K', 'L'),
                  ('L', 'END')]
input_turn_locations = [[(1, 'START'), (2, 'START'), (3, 'START'), (4, 'START')],
               [(1, 'A'), (2, 'C'), (3, 'START'), (4, 'START')],
               [(1, 'B'), (2, 'D'), (3, 'A'), (4, 'C')],
               [(1, 'END'), (2, 'END'), (3, 'B'), (4, 'D')],
               [(3, 'END'), (4, 'END')]]
input_turns = len(input_turn_locations)
start_node_name = 'START'
end_node_name = 'END'

#Graph
G = nx.Graph()
G.add_nodes_from(node_names)
G.add_edges_from(input_tunnels)

#Custom Looks
node_sizes = len(node_names) * 50
se_node_sizes = node_sizes * 1.5

#Choose Node Positions
pos = nx.spring_layout(G)

#Build plot
fig = plt.figure()

def highlight_node(node, highlight_color):
    node.set_color(highlight_color) 
    node.set_edgecolor(line_color)

def draw_node(node_name, node_color, node_size, line_color):
    node_list = []
    node_list.append(node_name)
    node = nx.draw_networkx_nodes(G, pos, nodelist=node_list, node_color=node_color,
               node_size=node_size)
    node.set_edgecolor(line_color)
    return (node)

def draw_nodes(node_names, node_color, node_size, line_color):
    nodes = {}
    for name in node_names:
        node = draw_node(name, node_color, node_size, line_color)
        nodes[name] = node
    return (nodes)

def get_odd_ants():
    odd_ants = []
    all_ants = []
    for turn in range(0,input_turns):
        for ant_move in input_turn_locations[turn]:
            if ant_move[1] != start_node_name and ant_move[0] not in all_ants:
                if turn % 2 == 1:
                    odd_ants.append(ant_move[0])
                all_ants.append(ant_move[0])
    print(all_ants)
    print("ODD" + str(odd_ants))
    return (odd_ants)

def update(num):
   
    #Restart:
    fig.clear()
    odd_ants = get_odd_ants()
    print(num)

    # default nodes & tunnels:
    tunnels = nx.draw_networkx_edges(G, pos, edge_color=line_color, width=2.0)
    nodes = draw_nodes(node_names, default_node_color, node_sizes, line_color)

    # start and end nodes
    s_node = draw_node(start_node_name, se_node_color, se_node_sizes, line_color)
    e_node = draw_node(end_node_name, se_node_color, se_node_sizes, line_color)
    
    # highlight occupied nodes
    if num < input_turns:
        current_node_names = [x[1] for x in input_turn_locations[num]]
        if start_node_name in current_node_names:
            highlight_node(s_node, highlight_color)
        if end_node_name in current_node_names:
            highlight_node(e_node, highlight_color)
        for move in input_turn_locations[num]:
            if move[0] in odd_ants: 
                highlight_node(nodes[move[1]], odd_ant_color)
            else:
                highlight_node(nodes[move[1]], even_ant_color)

    #labels
    room_names = nx.draw_networkx_labels(G, pos, font_size=8,
                                         labels=dict([(start_node_name, start_node_name),
                                                      (end_node_name, end_node_name)]),
                                         font_family='sans-serif')
  
    #set the background color
    fig.set_facecolor(bg_color)
   
    # hide the silly axis
    plt.axis('off') 


if __name__ == "__main__":
    ani = FuncAnimation(fig, update, frames=input_turns + 1, interval=1000, repeat=True)
    plt.show()
