const Task10 = require("./Task10");
const Task11 = require("./Task11");
const Task12 = require("./Task12");

let choice = 12;

switch (choice)
{
case 10:
    Task10("data/Task10Data.txt");
    break;
case 11:
    Task11("data/Task11Data.txt");
    break;
case 12:
    Task12("data/TestData.txt");
    break;
}
