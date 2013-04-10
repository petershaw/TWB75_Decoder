//
//  timeoutTest.c
//  AnalyserDude
//
//  Created by Peter Shaw on 4/10/13.
//
//

#include <stdio.h>
#include "../cu/cu.h"
#include "../../src/control/cron.h"

void *timeout(void){
    
}

TEST(testCronTimeoutAdd){
    cron_init();
    assertEquals(0, cron_count_timeouts());
    
    cron_set_timeout(1, 60, 0, 0, 0, timeout);
    assertEquals(1, cron_count_timeouts());
    
    cron_set_timeout(2, 0, 5, 0, 0, timeout);
    assertEquals(2, cron_count_timeouts());
    
    cron_set_timeout(1, 70, 0, 0, 0, timeout);
    assertEquals(2, cron_count_timeouts());
}

TEST(testCronTimeoutRemove){
    cron_init();
    assertEquals(0, cron_count_timeouts());
    
    cron_set_timeout(1, 60, 0, 0, 0, timeout);
    cron_set_timeout(2, 0, 5, 0, 0, timeout);
    cron_set_timeout(3, 0, 0, 10, 1, timeout);
    assertEquals(3, cron_count_timeouts());
    
    cron_remove_timeout(2);
    assertEquals(2, cron_count_timeouts());
    
}
