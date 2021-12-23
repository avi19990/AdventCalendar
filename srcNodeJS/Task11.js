const fs = require("fs");

function readOctoEnergyLevelsData(filename)
{
  let octoEnergyLevelsSource = fs.readFileSync(filename, { encoding : "ascii" });
  let octoEnergyLevelsString = octoEnergyLevelsSource.split("\r\n").join("");
  let octoEnergyLevels = [];

  for (let numStr of octoEnergyLevelsString)
    octoEnergyLevels.push(parseInt(numStr));

  return octoEnergyLevels;
}

function getNeighbours(index)
{
  const possibleDirections = [{ x : 0, y : -1 }, 
                              { x : 1, y : -1 }, 
                              { x : 1, y : 0 }, 
                              { x : 1, y : 1 }, 
                              { x : 0, y : 1 }, 
                              { x : -1, y : 1 }, 
                              { x : -1, y : 0 }, 
                              { x : -1, y : -1 }];

  let directions = [];
  for (let i = 0; i < possibleDirections.length; ++i)
  {
    let direction = { x : (index % 10) + possibleDirections[i].x, 
                      y : Math.floor(index / 10) + possibleDirections[i].y };
    if (direction.x >= 0 && direction.x < 10 && direction.y >= 0 && direction.y < 10)
      directions.push(direction.x + direction.y * 10);
  }

  return directions;
}

function simulateOctoEnergyStep(octoEnergyLevels)
{
  let flashedOctopuses = [];

  for (let i = 0; i < octoEnergyLevels.length; ++i)
  {
    if (flashedOctopuses.includes(i))
      continue;

    let toVisit = [i];
    while (toVisit.length != 0)
    {
      let current = toVisit.shift();
      octoEnergyLevels[current] += 1;

      if (octoEnergyLevels[current] > 9)
      {
        flashedOctopuses.push(current);
        octoEnergyLevels[current] = 0;
        toVisit = toVisit.filter(value => { return value != current; })

        for (let neighbour of getNeighbours(current))
          if (!flashedOctopuses.includes(neighbour))
            toVisit.push(neighbour);
      }
    }
  }

  return flashedOctopuses.length;
}

function getOctoFlashCount(octoEnergyLevels, stepCount)
{
  let flashCount = 0;
  for (let i = 0; i < stepCount; ++i)
    flashCount += simulateOctoEnergyStep(octoEnergyLevels);

  return flashCount;
}

function firstOctoFullFlash(octoEnergyLevel)
{
  let iteration = 1;
  while (simulateOctoEnergyStep(octoEnergyLevel) != 100)
    iteration += 1;

  return iteration;
}

function Task11(filename)
{
  let octoEnergyLevels = readOctoEnergyLevelsData(filename);

  console.log(`Solution to task 11 (part1): ${getOctoFlashCount([...octoEnergyLevels], 100)}`);
  console.log(`Solution to task 11 (part2): ${firstOctoFullFlash([...octoEnergyLevels])}`);
}

module.exports = Task11;