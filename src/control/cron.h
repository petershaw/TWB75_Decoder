//
//  cron.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/31/13.
//
//

#ifndef AnalyserDude_cron_h
#define AnalyserDude_cron_h
#include <stdint.h>

#ifdef IGNOREINTESTS
void interuptServiceRoutine(void);
#endif

// JOB DEFINITION - THE OF JOBS TO EXECUTE
// ---------------------------------------------
typedef struct cron_joblist {
    char identifyer;
    uint32_t total_ms;                           // total time in ms
    void (*fn)(void);                           // function to execute at timeout
    struct cron_joblist *next;               // next element
} cron_joblist_t;

cron_joblist_t *crontab;

// POINTERS TO THE FIRST AND THE LAST JOB
// ---------------------------------------------
typedef struct cron_borders {
    cron_joblist_t *first;
    cron_joblist_t *last;
} cron_borders_t;

cron_borders_t *crontab_ptr;

// GLOBAL TIMER
// ---------------------------------------------
volatile uint32_t       system_millisecunds_since_startup;
volatile uint32_t       cron_ms_for_execution_timer;
volatile uint8_t        system_days_since_startup;
volatile unsigned int   cron_seconds;
volatile unsigned int   cron_minutes;
volatile unsigned int   cron_hours;

// FUNCTIONS
// ---------------------------------------------
/**
 * inittialize the crontab and the timers
 */
void cron_init(void);

/**
 * calculate the timer in h m s
 */
void cron_calculate_uptime_hms(void);

/**
 * Add a new job to the crontab
 * A job that should called ever 1,5h can be written as:
 * char ident = cron_add_job(0, 0, 30, 1, fn_doSomething());
 * The retruned ident is the unique identifyer of the job.
 */
char cron_add_job(int ms, int sec, int min, int hous, void *fn);

/**
 * Removes a job with a specific identifyer from the queue
 */
void cron_remove_job(char);

/**
 * Clear the whole job definition table
 */
void cron_clear(void);

/**
 * Count the number of jobs in the table
 */
int cron_count(void);

#ifdef IGNOREINTESTS
void cron_increment_clock(void);
#endif

#endif
