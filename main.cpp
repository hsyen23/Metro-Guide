# include "graphStructure.h"
# include <fstream>
void readLineData(string, Graph &map);
int main(int argc, char **argv) {
    // read file in line directory
    Graph map(40);
    readLineData("RedLine.txt", map);
    readLineData("BlueLine.txt", map);
    readLineData("YellowLine.txt", map);
    readLineData("BrownLine.txt", map);
    readLineData("GreenLine.txt", map);
    string start;
    while(cin)
    {
        cout << "Enter Start Location" << endl;
        cin >> start;
        if (map.valueToIndex(start) != -1)
            break;
        cout << "Invalid Name! Try agian." << endl;
    }
    
    string end;
    while(cin)
    {
        cout << "Enter Destination" << endl;
        cin >> end;
        if (map.valueToIndex(end) != -1)
            break;
        cout << "Invalid Name! Try agian." << endl;
    }
    
    Dijkstra path(map.adjMatrix, map.NumberOfVertex, map.valueToIndex(start));
    stack<int> buffer = path.getPath(map.valueToIndex(end));
    // print out info
    cout << map.Vertices[buffer.top()].Value;
    buffer.pop();
    while(buffer.size() != 0)
    {
        cout << " -> " << map.Vertices[buffer.top()].Value;
        buffer.pop();
    }
    cout << endl;
    return 0;
}

void readLineData(string name, Graph &graph)
{
    string s = "./Lines/" + name;
    ifstream myfile;
    myfile.open(s);
    vector<string> buffer;
    if (myfile.is_open())
    {   
        while (myfile)
        {
            string tem;
            getline(myfile, tem);
            if (tem != "") // <- to avoid get blank line(enter)
                buffer.push_back(tem);
        }
    }
    // add path into map
    

    if (buffer.size() != 0)
        graph.addVertex(buffer[0]);
    
    for (int i = 0; i < buffer.size()-1; i++)
    {
        graph.addVertex(buffer[i+1]);
        int i1 = graph.valueToIndex(buffer[i]);
        int i2 = graph.valueToIndex(buffer[i+1]);
        graph.addEdge(i1, i2, 1);
    }
}
