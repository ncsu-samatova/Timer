/*
 * File:   test_timer.c
 * Author: sriram
 *
 * Created on Jun 5, 2012, 4:00:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <assert.h>

/*
 * Simple C Test Suite
 */

void test1() {
    char timerName [][256] = {"timer1", "timer2"};

    timer_start (timerName [0]);
    sleep (5);
    timer_stop (timerName [0]);

    timer_start (timerName [0]);
    sleep (2);
    timer_stop (timerName [0]);

    printf ("Sleep of %d seconds introduced and the timer says: %lf\n", 7, timer_get_total_interval (timerName [0]));
    timer_reset_timers ();

    timer_start (timerName [1]);
    sleep (2);
    timer_stop (timerName [1]);
    printf ("Sleep of %d seconds introduced and the timer says: %lf\n", 2, timer_get_total_interval (timerName [1]));

    timer_print_timers ();
}


void test_result_sort() {
    int i;
    timer_result_t *results;

    timer_start ("timerOuter");
    sleep (2);
    timer_start ("timerInner");
    sleep (3);
    timer_stop ("timerInner");
    timer_stop ("timerOuter");

    timer_start ("timerTwice");
    sleep (2);
    timer_stop ("timerTwice");

    timer_start ("timerMiddle");
    sleep (2);
    timer_stop ("timerMiddle");

    timer_start ("timerTwice");
    sleep (2);
    timer_stop ("timerTwice");

    printf("\nSORTED RESULTS:\n\n");

    printf("\nExpected results:\n");
    printf("timerOuter: 5\n");
    printf("timerInner: 3\n");
    printf("timerTwice: 4\n");
    printf("timerMiddle: 2\n");
    printf("\nActual results:\n");

    results = timer_get_results_sorted();
    for (i = 0; i < timer_get_num_timers(); i++) {
        printf("%s: %0.4lf\n", results[i].name, results[i].time);
    }
    free(results);

    printf("\nTREE RESULTS (without child excl):\n");

    printf("\nExpected results:\n");
    printf("+ [timerOuter] 5\n");
    printf("++ [timerInner] 3\n");
    printf("+ [timerTwice] 4\n");
    printf("++ [timerMiddle] 2\n");
    printf("\nActual results:\n");

    timer_print_results_tree(0);

    printf("\nTREE RESULTS (with child excl):\n");

    printf("\nExpected results:\n");
    printf("+ [timerOuter] 2\n");
    printf("++ [timerInner] 3\n");
    printf("+ [timerTwice] 2\n");
    printf("++ [timerMiddle] 2\n");
    printf("\nActual results:\n");

    timer_print_results_tree(1);
}


int main(int argc, char** argv)
{
    // To check if re-initting does not crash anything
    timer_init ();
    timer_finalize ();

    timer_init ();
    printf ("Timer initialized\n");
    //test1();

    printf ("List of timers: \n");
    timer_print_timer_names ();
    timer_finalize ();

    timer_init ();
    test_result_sort();
    timer_finalize ();

    printf ("Timer finalized\n");

    return (EXIT_SUCCESS);
}

