#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>

#define GLOBAL_PREFIX extern

#define MAX_TIMERS 256
#define MAX_NAME_LENGTH 256

typedef enum {
    TIMER_SUCCESS = 0,
    TIMER_NAME_NOT_FOUND,
    TIMER_INNACCESSIBLE,
    TIMER_ALREADY_RUNNING,
    TIMER_ALREADY_STOPPED,
    TIMER_ALREADY_INITIALIZED
} timer_error_t;

typedef enum {
    STOPPED = 0,
    RUNNING = 1
} timer_state_t;

typedef struct {
    char name [MAX_NAME_LENGTH];
    double firstStartClock;
    double lastStopClock;

    double currentStartClock;
    double lastInterval;
    double totalInterval;

    // For std.dev.
    double totalInvervalSqr;
    int totalIntervalCount;

    timer_state_t state;
} timer_id_t;

typedef struct {
    char name[MAX_NAME_LENGTH];
    double time;
    double stddev;
} timer_result_t;

typedef struct _timer_tree_t {
    char name[MAX_NAME_LENGTH];
    double time;

    struct _timer_tree_t *parent;
    int treeLevel;
    double timeExclChildren;
} timer_tree_t;

extern timer_error_t TIMER_STATUS;

int is_timer_initialized();

timer_error_t timer_init ();

timer_error_t timer_finalize ();

timer_error_t timer_start (const char *);

timer_error_t timer_stop (const char *);

timer_error_t timer_reset (const char *);

void timer_reset_timers ();

/*
 * This function return the current interval,
 * i.e. the interval between the last "timer_start"
 * and now.
 */
double timer_get_current_interval (const char *);

/*
 * This function return the last "recorded" interval.
 * i.e. the interval between the last "timer_start"
 * and "timer_stop"
 */
double timer_get_last_interval (const char *);

double timer_get_total_interval (const char *);

timer_id_t * timer_get_timer_object (const char *);

void timer_stop_timers ();

void timer_print_timers_short ();

void timer_print_timers ();

void timer_print_timer_names ();

timer_error_t timer_print_timer (const char *);

uint32_t timer_get_num_timers ();

char** timer_get_timer_names ();

timer_result_t * timer_get_results_sorted();

timer_tree_t * timer_get_results_tree();

// Prints all timers in a tree format (indented children below parent timers)
// If excludeChildTime is true (non-zero), the time printed for a timer is the
// difference of its full value and the sum of the full values of all child
// timers. Otherwise, time printed is simply the full value for each timer.
void timer_print_results_tree(int excludeChildTime);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif
