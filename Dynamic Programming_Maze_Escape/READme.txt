Configuration ulimit -s 100000

1. BFS 
MAXIMUM MAZE SIZE : 300X300
Algorithms :
	whenever agent call move function, my agent expand fringe list by using sensing information with First In First Out property.
	Because, BFS Algorithm should have to traverse the node at the low depth.
	Also, To prevent worthless traverse (for example, infinity loop like : a->b->a->b) agent checks is the Node already visited or not.
	if the node did not visited, then put in the fringe list

2. ASTAR
MAXIMUM MAZE SIZE : 300X300
Algorithms :
	whenever agent call move function, if the node is not update the heuristic value, then my agent update the heuristic value and actual cost to the node.
	if the node was already updated the heuristic value, then my agent try to expand fringe list by using check_visted function.
	if check_visited function return the Coordinate object, it means that agent already visited the Coordinate. So when it return the object agent compare current cost to the Coordinate with past cost to the Coordinate
	if the current cost is smaller than past cost, then agent update the shortest path to the Coordinate, and put the Coordinate at fringe (which is ordered by ascending order) again to update other path cost.  
	
3. DFS
MAXIMUM MAZE SIZE : 300X300
Algorithms :
	whenever agent call move function, agent check is the shortest path to the Coordinate, is the Coordinate at the Limit, and is there any fringe to visit.
	By using map STL and IsShortes function, I can constuct cost_map which contain the Coordinate and current least cost to the Coordinate.
	If my agent traverse the Coordinates within Limit, then put the Coordinates at fringe ( which has property of Last in First Out ) if the path to Coordinate is shortest path until now.
	If my agent traverse the Coordinates at Limit, then put the Coordinates at next_fringe ( which has property of Last in First Out ), and update the shortest path to the Coordinates.
	whenever fringe is empty, it means that agent traverse all Coordinates within Limit. So agent extend Limit and update fringe with next_fringe elements.
	By doing this, agent can remove useless path record. Thus, agent can keep only useful path. Also, it make agent dont reapeat the node which 	constitude the path.
	As a result, traverse like BFS and use memory like DFS