/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[4];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and prompt for players names
    // initialize each of the players in the array
    printf("Welcome to Jeopardy! Please Enter your Names:\n");
    for(int i=0; i<=4; i++){
        scanf("%s",&players[i].name);
    }
    printf("Thank you.\n");

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        char **token;
        *token[0] = "Who is";
        *token[1] = "What is";
        
        int game_return;
        
        initialize_game();
        game_return = run_game(token);
        return 0;

    }

    
}
void show_results(player *players){
    for(int i = 0; i <= 4; i++){
        printf("Name: %s\tScore:%d\n", player[i].name, player[i].score);
    }
}

void tokenize(char *input, char **tokens){

    const char *s1 = *tokens[0];
    const char *s2 = *tokens[1];

    const char token1* = strtok(input, *tokens[0]);
    const char token2* = strtok(input, *tokens[1]);

    if(token1 != ''){
        input = token1;
    }
    else if(token2 != ''){
        input = token2;
    }
    else{
        printf("ERROR. NO INPUT DETECTED\n");
    }
}

int run_game(char **token){

    // Execute the game until all questions are answered
    int questions_remaining = sizeof(questions);
    bool correct;
    char *category;
    int value;
    char *response;


    while(questions remaining > 0){
        for(int i =0; i < sizeof(players); i++){
            printf("'%s's Turn\n Please choose from the following questions\n
                (hint: first enter category and hit enter, then enter the dollar 
                    amount and hit enter):\n\n", player[i].name);
            
            display_categories();
            
            printf("\n\n");
            scanf("%s", &category);
            scanf("%d", value);
            printf("\n");
            
            if(already_answered){
                printf("Question has already been answered. Please choose another");
                i--;
            }
            else{
                display_question(category, value);
                scanf("%s", response);                                  //Takes response
                
                tokenize(response,token);                               //extracts answer from response
                correct = valid_answer(category,value,response);
                if(correct){
                    printf("Correct! You may now choose another question.\n\n");
                    player[i].score += value;
                    i--;
                }
                else{
                    prinf("Unfortunately, that is incorrect, or you forgot to say \"What is/Who is\".\n\n");
                }
                question_answered(category, value);
                questions_remaining--;
                if(questions_remaining<=0){
                    break;
                }
            }                
        }
    }
    
    // Display the final results and exit
    show_results(players);

    return EXIT_SUCCESS;

}

//Alex Trebek <> Kebert Xela