#include <iostream>

struct node {
	int value;
	int cost;
	int stage_value;
	int node_cost;
};
#define min(x, y) ((x) < (y) ? (x) : (y))
//#define DEBUG
//#define TEST_CASE_1

#ifdef TEST_CASE_1
const int N = 5;
const int Q = 11;

struct node a[N+1] = {{0, 0, 0, 0}, 
	{10, 10000},
	{30, 1000},
	{20, 100},
	{50, 10},
	{40, 1}
};

int test_m[Q+1] = {0,55,50,45,40,35,30,25,20,15,10,5};

#else
int N;
int Q;
struct node *a;
int *test_m;

#endif

int findMiddle(int a, int b, int c) {
    if ((a - b) * (c - a) >= 0) {
        return a;
    } else if ((b - a) * (c - b) >= 0) {
        return b;
    } else {
        return c;
    }
}

int findMinOfThree(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int subtree_cost(int elected, int node1, int node2, int m, int father) {
	int cost;

	if(a[elected].value == m) {
		cost = 0;
	} else {
		if(elected == father) cost = a[elected].cost;
		else cost = a[elected].node_cost;
	}

	int v1 = (node1 == father)?a[node1].value:a[node1].stage_value;
	int v2 = (node2 == father)?a[node2].value:a[node2].stage_value;

	int middle = findMiddle(m, v1, v2);
	if(middle == m) return cost;

	int c1 = (node1 == father)?a[node1].cost:a[node1].node_cost;
	int c2 = (node2 == father)?a[node2].cost:a[node2].node_cost;
	
	return cost + min(c1, c2);
}

void calculate_cost_on_the_node(int i, int m) {
	if(2*i > N) { //this node doesn't have children
		a[i].stage_value = a[i].value;
	      	if(a[i].value == m){
			a[i].node_cost = 0;	
	      	} else {
			a[i].node_cost = a[i].cost;
		}
#ifdef DEBUG
		std::cout << i << ":" << a[i].value << "," 
			<< a[i].cost << "," << a[i].stage_value << "," 
			<< a[i].node_cost << std::endl;
#endif
		return;
	}
	//calculate stage value
	a[i].stage_value = findMiddle(a[i].value, a[2*i].stage_value, a[2*i + 1].stage_value);

	//find lowest cost by electing three nodes in subtree
	int c1 = subtree_cost(i, 2*i, 2*i + 1, m, i);
	int c2 = subtree_cost(2*i, i, 2*i + 1, m, i);
	int c3 = subtree_cost(2*i+1, i, 2*i, m, i);
#ifdef DEBUG
	if(i <= 2) std::cout << i << ":" << c1 <<","<<c2<<","<<c3<<std::endl;
#endif
	a[i].node_cost = findMinOfThree(c1, c2, c3);	

#ifdef DEBUG
	std::cout << i << ":" << a[i].value << "," 
		<< a[i].cost << "," << a[i].stage_value << "," 
		<< a[i].node_cost << std::endl;
#endif
}

int calculate_min_cost(int m) {
	for(int i = N; i >= 1; i --) {
		calculate_cost_on_the_node(i, m);
	}
	return a[1].node_cost;
}


int main() {

	std::cin >> N;
	a = new node[N+1];
	for (int j = 1; j <= N; j ++){
		std::cin >> a[j].value;
		std::cin >> a[j].cost;
	}
	std::cin >> Q;
	test_m = new int[Q+1];
	for (int j = 1; j <= Q; j ++){
		std::cin >> test_m[j];
	}

	for (int j = 1; j <= Q; j ++){
		std::cout << calculate_min_cost(test_m[j]) << std::endl;
	}
	//std::cout << calculate_min_cost(15) << std::endl;
	return 0;
}



















