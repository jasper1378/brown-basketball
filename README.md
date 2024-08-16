# brown-basketball

## About

Fantasy basketball simulations created for my high school stats teacher, Mr. Brown.

<!---
Please note that I know nothing about basketball.
--->

## Installation

Acquire the sources
```
$ git clone https://github.com/jasper1378/brown-basketball.git
$ cd brown-basketball
$ git submodule update --init --recursive --remote
```
Build
```
$ make -C deps/libconfigfile
$ make
```
Install
```
$ make install
```

## Usage

This program simulates fantasy basketball games based on a provided database of players and reports various statistical results.

### Database

The player database takes the form of a configuration file passed to the program via a command-line argument. The configuration file must possess a specific format; an example is provided below.
```
player_database = [

  {
    name = "Joel Embiid";
    positions = ["PG","SG","PF","SF","C"];
    rank = 1;
    draft_range_begin = 1;
    draft_range_end = 6;
    points = 34.70;
    rebounds = 11.00;
    assists = 5.60;
    steals = 1.20;
    blocks = 1.70;
    threes = 1.40;
    field_goals_made = 11.50;
    field_goals_attempted = 21.80;
    free_throws_made = 10.20;
    free_throws_attempted = 11.60;
  },

  {
    name = "Nikola Jokic";
    positions = ["PG","SG","PF","SF","C"];
    rank = 2;
    draft_range_begin = 1;
    draft_range_end = 6;
    points = 26.40;
    rebounds = 12.40;
    assists = 9.00;
    steals = 1.40;
    blocks = 0.90;
    threes = 1.10;
    field_goals_made = 10.40;
    field_goals_attempted = 17.90;
    free_throws_made = 4.50;
    free_throws_attempted = 5.50;
  },

  {
    name = "Shai Gilgeous-Alexander";
    positions = ["PG","SG","PF","SF","C"];
    rank = 3;
    draft_range_begin = 1;
    draft_range_end = 6;
    points = 30.10;
    rebounds = 5.50;
    assists = 6.20;
    steals = 2.00;
    blocks = 0.90;
    threes = 1.30;
    field_goals_made = 10.60;
    field_goals_attempted = 19.80;
    free_throws_made = 7.60;
    free_throws_attempted = 8.70;
  },

  ...
];
```
The following is a description of the various fields.
- `name`, `string`, player name
- `positions`, `array<string>`, possible player game positions (one or more of `PG, SG, SF, PF, C`)
- `rank`, `integer`, the rank of the player, currently meaningless (I think)
- `draft_range_begin`, `integer`, the first draft pick where the player is likely to be chosen
- `draft_range_end`, `integer`, the last draft pick where the player is likely to be chosen
- `points`. `float`, average player points per game
- `rebounds`, `float`, average player rebounds per game
- `assists`, `float`, average player assists per game
- `steals`, `float`, average player steals per game
- `threes`, `float`, average player 3's per game
- `field_goals_made`, `float`, average player field goals made per game
- `field_goals_attempted`, `float`, average player field goals attempted per game
- `free_throws_made`, `float`, average player free throws made per game
- `free_throws_attempted`, `float`, average player free throws attempted per game

### Configuration

For optimization reasons, certain settings must be configured in the program before compilation. These settings can be found in [include/user_settings.hpp](user_settings.hpp).
- \<variable name\>, \<data type\>, \<description\>
- `g_k_trial_count`, `unsigned long int`, number of trials preformed
- `g_k_team_size`, `int`, number of players on a team
- `g_k_league_size`, `int`, number of teams in a league
- `g_k_pool_size`, `int`, number of players in database

### Simulation

The simulation involves randomly generating leagues, scoring the teams, and then recording the results. Although I said 'random', the generation is biased in such a way to better reflect reality. For example, it will take into acccount properly filling the various positions on a team and the likelihood that a player will be drafted in a specific round.

### Progress

During the simulation, the program will print the percent completed and the estimated time remaining. When the simulation is finished, the program will print the total time taken. All of this is printed to stderr so as not to interfere with the printing of the main results.

### Results

After running the simulation, the program will print two sets of statistics in CSV format to standard output.

Note that the "player statistics categories" as mentioned below are: points, rebounds, assists, steals, blocks, 3's, field goals, free throws.

The first consists of the probabilities that each player will be drafted in a team whose rank is 1 or 1-4 (Mr. Brown tells me that the number 4 is important for some reason...) in each of the player statistics categories.

The second consists of mean, minimum, maximum, and standard standard deviation of each of the player statistics categories for each team ranked 1-... in each of the player statistics categories.

## License

See [LICENSE](LICENSE) for details.
