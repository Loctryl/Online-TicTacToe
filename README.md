# Online TicTacToe

## Context
This is a student project with a team of 4 people, during 2 weeks.

The first goal was to learn about networking and threads architecture. The game is only used to illustrate the system behind.

## Technical part
There are 2 applications there : the server and the client.
Each one support network communication on a different thread.

The server manages all the current games, keeping the datas. It also sends all these data on a web server displaying played games, also in a thread.

Client provides possibility to custom your nickname, and the local address to connect. Of course, it gets the inputs of the player.
