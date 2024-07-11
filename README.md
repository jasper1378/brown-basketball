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
    name = "Aaron Gordon";
    positions = ["PF"];
    draft_range_begin = 109;
    draft_range_end = 144;
    points = 16.00;
    rebounds = 6.30;
    assists = 2.80;
    steals = 0.70;
    blocks = 0.70;
    threes = 1.10;
    field_goals_made = 6.20;
    field_goals_attempted = 11.40;
    free_throws_made = 2.60;
    free_throws_attempted = 3.90;
  },

  {
    name = "Al Horford";
    positions = ["PF","C"];
    draft_range_begin = 109;
    draft_range_end = 144;
    points = 9.40;
    rebounds = 6.60;
    assists = 3.00;
    steals = 0.60;
    blocks = 1.10;
    threes = 1.70;
    field_goals_made = 3.50;
    field_goals_attempted = 7.50;
    free_throws_made = 0.60;
    free_throws_attempted = 0.80;
  },

  {
    name = "Alex Caruso";
    positions = ["PG","SG"];
    draft_range_begin = 157;
    draft_range_end = 180;
    points = 6.30;
    rebounds = 3.20;
    assists = 3.30;
    steals = 1.60;
    blocks = 0.60;
    threes = 0.90;
    field_goals_made = 2.20;
    field_goals_attempted = 5.10;
    free_throws_made = 1.10;
    free_throws_attempted = 1.40;
  },

  ...
];
```
The following is a description of the various fields.
- `name`, `string`, player name
- `draft_range_begin`, `integer`, the first draft pick where the player is likely to be chosen
- `draft_range_end`, `integer`, the last draft pick where the player is likely to be chosen
- `positions`, `array<string>`, possible player game positions (one or more of `PG, SG, SF, PF, C`)
- `points`. `float`, average player points per game
- `rebounds`, `float`, average player rebounds per game
- `assists`, `float`, average player assists per game
- `steals`, `float`, average player steals per game
- `threes`, `float`, average player 3's per game
- `field_goals_made`, `float`, average player field goals made per game
- `field_goals_attempted`, `float`, average player field goals attempted per game
- `free_throws_made`, `float`, average player free throws made per game
- `free_throws_attempted`, `float`, average player free throws attempted per game

<!---
If perhaps you are storing player statistics in a spreadsheet, a CSV (or rather tab-separated) file in the format below can be easily converted to the configuration file format using the Vim macro specified in [vim_macro_format_database.txt](vim_macro_format_database.txt).
```
name	positions	draft_range_begin	draft_range_end	points	rebounds	assists	steals	blocks	threes	field_goals_made	field_goals_attempted	free_throws_made	free_throws_attempted
Aaron Gordon	PF	109	144	16.00	6.30	2.80	0.70	0.70	1.10	6.20	11.40	2.60	3.90
Al Horford	PF,C	109	144	9.40	6.60	3.00	0.60	1.10	1.70	3.50	7.50	0.60	0.80
Alex Caruso	PG,SG	157	180	6.30	3.20	3.30	1.60	0.60	0.90	2.20	5.10	1.10	1.40
...
```
--->

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
