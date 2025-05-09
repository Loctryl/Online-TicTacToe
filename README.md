# Online TicTacToe

## Context
This is a student project with a team of 4 people, during 2 weeks.

The first goal was to learn about networking and threads architecture. The game is only used to illustrate the system behind.

## Technical part
There are 2 applications there : the server and the client.
Each one support network communication on a different thread.

The server manages all the current games, keeping the datas. It also sends all these data on a web server displaying played games, also in a thread.

Client provides possibility to custom your nickname, and the local address to connect. Of course, it gets the inputs of the player.

We use SFML 2.6 for rendering.

## Screenshots
- Client menu : 

![image](https://github.com/user-attachments/assets/530520da-106d-41e6-8066-59bf21ebd31b)

- Client view of the game : 

![image](https://github.com/user-attachments/assets/a8062d03-b090-47e5-adfb-0d0a8a8cf3f0)

- Website's game tracking : 

![image](https://github.com/user-attachments/assets/c72bf394-c434-4f8d-819e-62d3d75e0648)

- Server's request tracking : 

![image](https://github.com/user-attachments/assets/af81a753-4563-4125-b16c-576fd72bd1bd)

