/*
--- Day 4: Ceres Search ---

"Looks like the Chief's not here. Next!" One of The Historians pulls out a device and pushes the only button on it. After a brief flash, you recognize the interior of the Ceres monitoring station!

As the search for the Chief continues, a small Elf who lives on the station tugs on your shirt; she'd like to know if you could help her with her word search (your puzzle input). She only has to find one word: XMAS.

This word search allows words to be horizontal, vertical, diagonal, written backwards, or even overlapping other words. It's a little unusual, though, as you don't merely need to find one instance of XMAS - you need to find all of them. Here are a few ways XMAS might appear, where irrelevant characters have been replaced with .:

..X...
.SAMX.
.A..A.
XMAS.S
.X....

The actual word search will be full of letters instead. For example:

MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX

In this word search, XMAS occurs a total of 18 times; here's the same word search again, but where letters not involved in any XMAS have been replaced with .:

....XXMAS.
.SAMXMS...
...S..A...
..A.A.MS.X
XMASAMX.MM
X.....XA.A
S.S.S.S.SS
.A.A.A.A.A
..M.M.M.MM
.X.X.XMASX

Take a look at the little Elf's word search. How many times does XMAS appear?

--- Part Two ---

The Elf looks quizzically at you. Did you misunderstand the assignment?

Looking for the instructions, you flip over the word search to find that this isn't actually an XMAS puzzle; it's an X-MAS puzzle in which you're supposed to find two MAS in the shape of an X. One way to achieve that is like this:

M.S
.A.
M.S

Irrelevant characters have again been replaced with . in the above diagram. Within the X, each MAS can be written forwards or backwards.

Here's the same example from before, but this time all of the X-MASes have been kept instead:

.M.S......
..A..MSMS.
.M.S.MAA..
..A.ASMSM.
.M.S.M....
..........
S.S.S.S.S.
.A.A.A.A..
M.M.M.M.M.
..........

In this example, an X-MAS appears 9 times.

Flip the word search from the instructions back over to the word search side and try again. How many times does an X-MAS appear?
*/

#include <iostream>

#include <QFile>
#include <QList>

using namespace std;

int search1(int x, int y, QList<QList<char>> matrix)
{
    int xmax = matrix.size() - 1;
    int ymax = matrix[0].size() - 1;
    int res = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if  (x + 3*i < 0 || x + 3*i > xmax || y + 3*j < 0 || y + 3*j > ymax)
            {
                continue;
            }
            if (matrix[x+i][y+j] == 'M'
                    && matrix[x+2*i][y+2*j] == 'A'
                    && matrix[x+3*i][y+3*j] == 'S')
            {
                res += 1;
            }

        }
    }
    return res;
}

int search2(int x, int y, QList<QList<char>> matrix)
{
    int xmax = matrix.size() - 1;
    int ymax = matrix[0].size() - 1;
    if (x + 1 > xmax || x - 1 < 0 || y + 1 > ymax || y - 1 < 0)
    {
        return 0;
    }
    for (int step = -1; step <= 1; step += 2)
    {
        if (matrix[x+step][y-1] == 'M'
                && matrix[x+step][y+1] == 'M'
                && matrix[x-step][y-1] == 'S'
                && matrix[x-step][y+1] == 'S')
        {
            return 1;
        }
        if (matrix[x+1][y-step] == 'M'
                && matrix[x-1][y-step] == 'M'
                && matrix[x+1][y+step] == 'S'
                && matrix[x-1][y+step] == 'S')
        {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QString s;
    if (argc == 2)
    {
        s = argv[1];
    }
    else
    {
        s = "input";
    }

    QFile inf(s);

    if (!inf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Ouverture fichier input impossible..." << endl;
        return -1;
    }

    QList<char> *line;
    line = new QList<char>();
    line->reserve(150);
    QList<QList<char>> matrix;
    matrix.reserve(150);

    while (!inf.atEnd())
    {
        char c;
        inf.getChar(&c);
        if (c == '\n')
        {
            matrix.append(*line);
            line = new QList<char>();
            line->reserve(150);
        }
        else
        {
            line->append(c);
        }
    }
    delete line;

    int rep1 = 0, rep2 = 0;

    for(int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] == 'X')
            {
                rep1 += search1(i, j, matrix);
            }
            if (matrix[i][j] == 'A')
            {
                rep2 += search2(i, j, matrix);
            }
        }
    }

    cout << "Réponse 1 : " << rep1 << endl;
    cout << "Réponse 2 : " << rep2 << endl;


}
