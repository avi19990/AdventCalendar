const fs = require("fs");

function readSyntaxLinesData(filename)
{
    let syntaxLinesSource = fs.readFileSync(filename, { encoding: 'ascii' });
    let syntaxLines = syntaxLinesSource.split("\r\n");

    return syntaxLines;
}

function getSyntaxLineErrorElement(line)
{
    const oppositeBrackets = { ")" : "(", "]" : "[", "}" : "{", ">" : "<" };

    let syntaxElementStack = [];

    for (let element of line)
    {
        if ("([{<".includes(element))
            syntaxElementStack.push(element);
        else
        {
            let tmp = syntaxElementStack.pop();
            if (tmp != oppositeBrackets[element])
                return element;
        }
    }

    return "";
}

function getSyntaxErrorScore(syntaxLines)
{
    var errorElementCount = { ")" : 0, "]" : 0, "}" : 0, ">" : 0 };

    for (let line of syntaxLines)
    {
        let errorElement = getSyntaxLineErrorElement(line);
        errorElementCount[errorElement] += 1;
    }

    let score = 0;
    score += errorElementCount[")"] * 3;
    score += errorElementCount["]"] * 57;
    score += errorElementCount["}"] * 1197;
    score += errorElementCount[">"] * 25137;

    return score;
}

function getSyntaxLineCompletionElements(line)
{
    let syntaxElementStack = [];

    for (let element of line)
    {
        if ("([{<".includes(element))
            syntaxElementStack.push(element);
        else
            syntaxElementStack.pop();
    }

    syntaxElementStack.reverse();
    return syntaxElementStack;
}

function getSyntaxCompletionScore(syntaxLines)
{
    const scoreValues = { "(" : 1, "[" : 2, "{" : 3, "<" : 4 };

    let scores = [];
    for (let line of syntaxLines)
    {
        if (getSyntaxLineErrorElement(line) != "")
            continue;
        
        let completionElements = getSyntaxLineCompletionElements(line);

        let score = 0;
        for (let element of completionElements)
        {
            score *= 5;
            score += scoreValues[element];
        }

        scores.push(score);
    }

    scores.sort((a, b) => { return a - b; });

    return scores[Math.floor(scores.length / 2)]
}

function Task10(filename)
{
    let syntaxLines = readSyntaxLinesData(filename);

    console.log(`Solution to task 10 (part1): ${getSyntaxErrorScore(syntaxLines)}`);
	console.log(`Solution to task 10 (part2): ${getSyntaxCompletionScore(syntaxLines)}`);
}

module.exports = Task10;