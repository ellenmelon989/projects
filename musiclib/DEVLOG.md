# Dev Log:

## Ellen Yu

### 2024-01-03 - proposal, branch
- timeline in proposal: 10 minutes
- branch creation: 2 minutes
### 2024-01-04 - setting up music library
- setting up lib, list, makefile: 10 min
- helping search how to play music: 20 min
- adding server and client files for networking: 10 min
### 2024-01-05 - setting up music library and sdl
- searched for how to properly include external library: 35 min
- changed makefile: 5 min
### 2024-01-06 to -07 - setting up music library and sdl
- researched more on sdl library includes: 60 min
- tried to accurately include sdl (unsuccessful): 30 min
- adding signals and main setup: 15 min
### 2024-01-08 - troubleshooting
- adding signals and adding to main: 25 min
- creating err: 5 min
- fixing compiling and editing makefile: 40 min
### 2024-01-09 - troubleshooting and server/client 
- actually fixing makefile and compiling issues: 50 min 
- working on server/client connection and exchanging information between them: 60 min
### 2024-01-10 - server/client 
- adding functionality with server and client: 2 hr
### 2024-01-11 - altering playlist code
- writing playlist functions: 1 hr 
- implementing playlist things in server: 1 hr
### 2024-01-12 - altering playlist code and server
- figuring out issues in server and playlist functions: 2 hr
### 2024-01-13 to -15 - fixing playlist, server, shared memory, semaphores
- adding playlist and server/client function: 3 hr
- implementing shared memeory for storage of playlists: 1 hr 30 min
- troubleshooting shared memory and why it isn't the same after forking: 3 hr
- trying semaphores to synchronize: 2 hr
- updating proposal and readme: 20 min

## Jennifer Ye

### 2024-01-03 - proposal, branch
- part of proposal: 40 minutes
- branch creation: 2 minutes

### 2024-01-04 - library
- search for music api/library: 30 minutes
- audio playback SDL library download: 5 minutes
- audio code files: 5 minutes
- song playback functions brainstorming in .h: 15 minutes

### 2024-01-05 - library
- three song playback functions (err, initializeSDL, playSong): 40 minutes

### 2024-01-07 - server, client
- watched tutorials on SDL library: 60 minutes
- client now sends song name and artist name: 30 minutes
- server now receives song and artist name from client and adds it to library: 30 minutes

### 2024-01-08 - playlist
- playlist.h file completed with the six new functions: 20 minutes
- users can now create playlists as a struct node**: 15 minutes
- users can now search for a playlist: 10 minutes
- users can now add songs to a specified playlist: 15 minutes
- playlists can now be printed out with all of its contents: 10 minutes
- playlists can now be deleted: 10 minutes
- playlists can now be alphabetized: 15 minutes

### 2024-01-09 - audio
- pauseSong function using SDL: 10 minutes
- research on homebrew's mpg123: 30 minutes
- audio.h file completed with the four new functions: 15 minutes
- users can now play songs using mpg123 with the song name: 20 minutes
- users can now pause songs: 10 minutes
- users can now skip songs: 10 minutes
- users can now rewind songs: 15 minutes

### 2024-01-10 - songs, server
- researched mpg123: 15 minutes
- tested mp3 file with mpg123: 10 minutes
- added ten songs to library: 20 minutes
- fixed server's four compile errors: 30 minutes
- tested server/client: 20 minutes

### 2024-01-11 - server/client troubleshooting to play a song
- edited makefile to be neater: 5 minutes
- SIGCONT / ctrl+q implementation in server, client: 45 minutes
- getCurrSong and sendSong functions as part of server/client communication: 30 minutes