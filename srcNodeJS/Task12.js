const fs = require("fs");

function readPathsData(filename)
{
  let pathsSource = fs.readFileSync(filename, { encoding : "ascii" });
  let paths = pathsSource.split("\r\n");
  
  let pathsGraph = [];
  for (let i = 0; i < paths.length; ++i)
  {
    let [a, b] = paths[i].split("-");

    if (pathsGraph[a] == null)
      pathsGraph[a] = [];
    pathsGraph[a].push(b);

    if (pathsGraph[b] == null)
      pathsGraph[b] = [];
    pathsGraph[b].push(a);
  }

  return pathsGraph;
}

function isCaveBig(cave)
{
  return cave[0] >= "A" && cave[0] <= "Z";
}

function findPaths(cave, pathsGraph, visited)
{
  let visitedInPath = [...visited];
  if (!isCaveBig(cave))
    visitedInPath.push(cave);

  if (cave == "end")
    return 1;
  
  let pathsCount = 0;
  for (neighbour of pathsGraph[cave])
    if (!visitedInPath.includes(neighbour))
      pathsCount += findPaths(neighbour, pathsGraph, visitedInPath);
  
  return pathsCount;
}

function findPathsWithDouble(cave, pathsGraph, visited, hasDoubled)
{
  let visitedInPath = [...visited];
  if (!isCaveBig(cave))
    visitedInPath.push(cave);

  if (cave == "end")
    return 1;
  
  let pathsCount = 0;
  for (neighbour of pathsGraph[cave])
  {
    if (neighbour == "start")
      continue;

    let isNeighbourVisited = visitedInPath.includes(neighbour);
    if (isNeighbourVisited && hasDoubled)
      continue;

    pathsCount += findPathsWithDouble(neighbour, pathsGraph, visitedInPath, isNeighbourVisited || hasDoubled);
  }
  
  return pathsCount;
}

function getPathCount(pathsGraph)
{
  return findPaths("start", pathsGraph, []);
}

function getPathCountWithDouble(pathsGraph)
{
  return findPathsWithDouble("start", pathsGraph, [], false);
}

function Task12(filename)
{
  let pathsGraph = readPathsData(filename);

  console.log(`Solution to task 12 (part1): ${getPathCount(pathsGraph)}`);
  console.log(`Solution to task 12 (part2): ${getPathCountWithDouble(pathsGraph)}`);
}

module.exports = Task12;