#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>
#include <time.h>

#define null NULL
#define error_Make_File "Error To Make File"
#define error_Open_File "Error To Open File"
#define error_Add_Game "Erro To Add Game"
#define error_Allocating_Memory "Error Allocating Memory"

void menu ( );
int read_Int ( char * Text );
char * read_Name ( char * Text );
void roulette ( FILE * file );
int add_Game ( FILE * file, char * name_Game ); 
FILE * remove_Game ( char * name_Game_Remove );
void show_Games ( );

void roulette ( FILE * file )
{
    if ( ! file )
    {
        printf ( "%s\n", error_Open_File );
        return ;
    }

    rewind ( file );

    int count_Games = 0;
    char assistant [ 50 ];

    while ( fgets ( assistant, sizeof ( assistant ), file ) )
    {
        assistant [ strcspn ( assistant, "\n" ) ] = '\0';
        if ( assistant [ 0 ] != '\0' && assistant [ 0 ] != '\n' )
        {
            count_Games ++;
        }
    }

    if ( count_Games < 0 )
    {
        printf ( "No Games Added !!!\n" );
        return ;
    }

    srand ( time ( null ) );
    int target = rand ( ) % count_Games;

    rewind ( file );
    count_Games = 0;

    printf ( "\nDraft Game ...\n\n" );
    fflush ( stdout );
    Sleep ( 1000 );
    system ( "cls" );

    for (int i = 0; i < 3; i++)
    {
        Sleep ( 1000 );
        printf ( "." );
        fflush ( stdout );
    }

    Sleep ( 1000 );
    system ( "cls" );
    Sleep ( 1000 );
    printf ( "\n" );

    while ( fgets ( assistant, sizeof ( assistant ), file ) )
    {
        assistant [ strcspn ( assistant, "\n" ) ] = '\0';
        if ( assistant [ 0 ] != '\0' && assistant [ 0 ] != '\n' )
        {
            if ( count_Games == target )
            {
                printf("\n  ----------------------------------------------");
                printf("\n              GAME CHOSE: %s    ", assistant);
                printf("\n  ----------------------------------------------\n\n");
            }

            count_Games ++;
        }
    }
}

int add_Game ( FILE * file, char * name_Game )
{
    if ( ! file )
    {
        printf ( "%s\n", error_Add_Game );
        return 0;
    }

    if ( name_Game == null || name_Game [ 0 ] == '\0' )
    {
        return 0;
    }

    fprintf ( file, "%s\n", name_Game );
    fflush ( file );
    return 1;
}

FILE * remove_Game ( char * game_Name_Remove )
{
    FILE * original = fopen ( "folders/games.txt", "r" );

    if ( ! original )
    {
        printf ( "%s\n", error_Make_File );
        return null;
    } 

    FILE * temp = fopen ( "folders/temp.txt", "w" );

    if ( ! temp )
    {
        printf ( "%s\n", error_Make_File );
        fclose ( original );
        return null;
    } 

    char assistant [ 50 ];
    int removed = 0;

    while ( fgets ( assistant , sizeof ( assistant ), original ) )
    {
        assistant [ strcspn ( assistant, "\n" ) ] = '\0';

        if ( strcmp ( assistant, game_Name_Remove ) != 0 )
        {
            fprintf ( temp, "%s\n", assistant );
        } else
            {
                removed = 1;
            }
    }

    fclose ( original );
    fclose ( temp );

    if ( removed == 0 )
    {
        remove ( "folders/temp.txt" );
        printf ( "Game not founded !!!\n\n" );
        return fopen ( "folders/games.txt", "a+" );
    } 

    remove ( "folders/games.txt" );
    
    if ( rename ( "folders/temp.txt", "folders/games.txt" ) != 0 )
    {
        printf ( "Error to renaming file !!!\n" );
        return null;
    }

    return fopen ( "folders/games.txt", "a+" );
}

void show_Games ( )
{
    printf ( "~~~~~~~~~~~~~~ List Games ~~~~~~~~~~~~~~\n" );

    FILE * read_File = fopen ( "folders/games.txt", "r" );

    rewind ( read_File );

    char assistant [ 50 ];

    while ( fgets ( assistant, sizeof ( assistant ), read_File ) )
    {
        assistant [ strcspn ( assistant, "\n" ) ] = '\0';
        
        if ( assistant [ 0 ] != '\0' )
        {
            printf ( "- %s\n", assistant );
        }
    }

    fclose ( read_File );
    printf ( "~~~~~~~~~~~~~~~~~~ // ~~~~~~~~~~~~~~~~~~\n" );
}

void menu ( )
{
    printf ( "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );
    printf ( "\n%s\n\n", "Welcome To Roulette =)\tWhat You Want To Do ?" );
    printf ( "%s\n", "1 - Roulette ->" );
    printf ( "%s\n", "2 - Add A Game" );
    printf ( "%s\n", "3 - Remove A Game" );
    printf ( "%s\n", "4 - Show The Games" );
    printf ( "%s\n\n", "0 - Exit" );
}

char * read_Name ( char * Text )
{
    char * word_Save_Game = ( char * ) malloc ( 50 * sizeof ( char ) );

    if ( ! word_Save_Game )
    {
        printf ( "%s\n", error_Allocating_Memory );
        return null;
    }

    system ( "cls" );

    printf ( "\n%s\n", Text );
    fgets ( word_Save_Game, 50, stdin );
    
    word_Save_Game [ strcspn ( word_Save_Game, "\n" ) ] = '\0';

    return word_Save_Game;
}

int read_Int ( char * Text )
{
    int value = 0;

    printf ( "%s\n", Text );
    scanf ( "%d", & value );

    while ( getchar ( ) != '\n' );

    return value; 
}

int main ( )
{
    system ( "cls" );

    if ( _access ( "folders", 0 ) != 0 )
    {
        if ( _mkdir ( "folders" ) != 0 )
        {
            printf ( "Error: Could not create 'folders' directory !!!\n" );
            return 1;
        } 
    }

    FILE * file = fopen ( "folders/games.txt", "a+" );

    if ( ! file ) 
    {
        printf ( "%s 01\n", error_Make_File );
        return 1;
    }

    int option = 0;

    do
    {
        system ( "cls" );

        menu ( );
        option = read_Int ( "Choose One Option :" );

        switch ( option )
        {
            case 1:
                {
                    system ( "cls" );
                    roulette ( file );
                    getchar ( );
                    break ;
                }

            case 2:
                {
                    char * word_Save_Game = read_Name ( "Write The Name To The Game:" );

                    if ( ! word_Save_Game )
                    {
                        printf (  "%s\n", error_Add_Game );
                        break ;
                    }

                    int answer = add_Game ( file, word_Save_Game );

                    system ( "cls" );

                    if ( answer == 1 )
                    {
                        printf ( "Game Added Successfully !!!\n" );
                    } else
                        {
                            printf ( "Invalid Name, Not Added !!!\n" );
                        }
                    
                    free ( word_Save_Game );
                    getchar ( );
                    break ;
                }
            
            case 3:
                {
                    char * word_Delete_Game = read_Name ( "Write The Name To Be Deleted:" );

                    if ( ! word_Delete_Game )
                    {
                        printf (  "%s\n", error_Add_Game );
                        break ;
                    }

                    fclose ( file );

                    FILE * new_File = remove_Game ( word_Delete_Game );

                    rewind ( new_File );
                    
                    if ( ! new_File )
                    {
                        printf ( "%s\n", "Error to open new file" );
                    } else
                        {
                            printf (  "%s\n", "Game removed !!!" );
                            fclose ( file );
                            file = new_File;
                        }

                    free ( word_Delete_Game );
                    getchar ( );
                    break ;
                }
            
            case 4:
                {
                    system ( "cls" );
                    show_Games ( file );
                    getchar ( );
                    break ;
                }

            default:
                break ;
        }
    } while ( option != 0 );
    
    fclose ( file );
    return 0;
}