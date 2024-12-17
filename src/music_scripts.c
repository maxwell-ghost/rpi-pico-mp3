#include "audio.h"

// 乐谱，三个数字一组，
//第一个表示音高，
//第二个表示高几个八度还是低几个八度
//第三个表示缩短原来的几倍
int8_t music_test[] = {
	0,0,1,  1,1,1,  1,2,1,  7,1,1,

	1,2,2,  7,1,2,  6,1,2,  5,1,2,  6,1,2,  5,1,2,  3,1,2,  2,1,2, 

	3,1,2,  5,1,2,  6,1,2,  5,1,2,  0,0,2,  5,1,2,  6,1,2,  5,1,2,

	6,1,1,  6,1,2,  6,1,2,  5,1,1,  5,1,2,  6,1,2,

	5,1,2,  3,1,1,  3,1,2,  0,0,2,  1,1,2,  2,1,2,  3,1,2,

};

int8_t music_script_faded[] = {
	1,ndot,nbar, 1,ndot,nbar, 1,ndot,nbar, 3,ndot,nbar, sep,0,0,
	
	6,ndot,nbar, 6,ndot,nbar, 6,ndot,nbar, 5,ndot,nbar, sep,0,0,
	
	3,ndot,nbar, 3,ndot,nbar, 3,ndot,nbar, 3,ndot,nbar, sep,0,0,
	
	7,ddot,nbar, 7,ddot,nbar, 7,ddot,nbar, 6,ddot,nbar, sep,0,0,


	0,ndot,bar, 1,ndot,bar, 1,ndot,bar, 6,ddot,bar,
	1,ndot,bar, conn,0,0, 6,ddot,bar, 1,ndot,bar, 2,ndot,bar, sep,0,0, // You were

	3,ndot,nbar, 1,ndot,bar, 1,ndot,bar, 5,ddot,bar, 3,ndot,nbar, 3,ndot,bar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 1,ndot,nbar, sep,0,0,



	7,ddot,nbar, conn,0,0, 7,ddot,nbar, 7,ddot,bar, 6,ddot,bar, 1,ndot,nbar, sep,0,0, // start

	0,ndot,bar, 1,ndot,nbar, conn,0,0, 6,ddot,bar, 1,ndot,bar, 6,ddot,bar, 1,ndot,bar, sep,0,0,
	2,ndot,bar,

	3,ndot,nbar, 1,ndot,bar, 1,ndot,bar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,



	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, conn,0,0, 1,ndot,nbar, conn,0,0, 
    2,ndot,bar, con,0,0, // Alive

	2,ndot,nbar, conn,0,0, 2,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0, 

	3,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0, 

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0,



	3,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0, //now

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0,

	3,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar2, conn,0,0, 2,ndot,bar2,
	2,ndot,bar, 2,ndot,bar2, 3,ndot,bar2, sep,0,0,



	2,ndot,bar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,bar, 0,ndot,bar, 
    3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0, //fantansy

	3,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, 1,ndot,bar, 
    1,ndot,bar2, conn,0,0, 2,ndot,bar2, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,bar, conn,0,0, 1,ndot,bar, conn,0,0, 
    1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,


    // where
	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar,
    con,0,0,

	6,ddot,bar, conn,0,0, 5,ddot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 
    5,ndot,bar, 5,ndot,bar2, 3,ndot,bar2, con,0,0,



	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 
    5,ndot,bar, 5,ndot,bar2, 3,ndot,bar2, con,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar,
    3,ndot,bar, sep,0,0, 

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 
    1,ndot,bar, conn,0,0, 6,udot,bar2, 4,ndot,bar2, con,0,0,


    // The monster
	4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, 0,ndot,bar, 
    5,ndot,bar, sep,0,0,

	3,ndot,bar, conn,0,0, 5,ndot,bar, 3,ndot,bar, conn,0,0, 5,ndot,bar, 
    3,ndot,bar, conn,0,0, 5,ndot,bar, 3,ndot,bar, 2,ndot,bar2, 5,ndot,bar2,
    con,0,0,

	4,ndot,nbar, conn,0,0, 4,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 
    3,ndot,nbar, sep,0,0,


    // I am faded
	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 3,ndot,nbar,
    sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 
    3,ndot,nbar, sep,0,0,


    // I am faded
	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 5,ndot,nbar,
    sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 
    3,ndot,nbar, sep,0,0,


    // These shadllow
	0,ndot,bar, 1,ndot,bar, 1,ndot,nbar, 1,ndot,bar, conn,0,0, 6,ddot,bar,
    1,ndot,bar,	2,ndot,bar, sep,0,0,

	3,ndot,nbar, conn,0,0, 1,ndot,bar, 1,ndot,bar, 5,ddot,bar, conn,0,0, 
    3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, 1,ndot,nbar, sep,0,0,


    // goadeeper
	7,ddot,nbar, conn,0,0, 7,ddot,nbar, conn,0,0, 7,ddot,bar, conn,0,0, 
    6,ddot,bar, 1,ndot,nbar, sep,0,0,

	0,ndot,bar, 1,ndot,nbar, conn,0,0, 2,ndot,bar, 1,ndot,bar, conn,0,0, 
    6,ddot,bar, 1,ndot,bar, 2,ndot,bar, sep,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,bar, 1,ndot,bar, 5,ndot,bar, conn,0,0, 
    5,ndot,bar2, conn,0,0, 3,ndot,bar2, conn,0,0, 3,ndot,nbar, sep,0,0,


    // alive
	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,nbar, conn,0,0, 2,ndot,bar, 
    con,0,0,

	2,ndot,nbar, conn,0,0, 2,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar,
    3,ndot,bar, sep,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0, 


    // now
	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 5,ndot,bar, 
    5,ndot,bar2, 3,ndot,bar2, con,0,0,

	3,ndot,bar, 1,ndot,bar, 5,ndot,bar, conn,0,0, 5,ndot,bar2, 3,ndot,bar2, conn,0,0, 
    3,ndot,bar, 1,ndot,bar, conn,0,0, 5,ndot,bar, 5,ndot,bar2, 2,ndot,bar2, con,0,0,


    // heart on fire
	2,ndot,bar, 1,ndot,bar, 1,ndot,bar, 3,ndot,bar, conn,0,0, 3,ndot,bar, 
    1,ndot,bar, conn,0,0, 5,ndot,bar, 5,ndot,bar2, 3,ndot,bar2, sep,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 
    5,ndot,bar, 5,ndot,bar2, 2,ndot,bar2, sep,0,0,


    // now? Another
	2,ndot,nbar, conn,0,0, 2,ndot,nbar, 0,ndot,bar, 1,ndot,bar2, conn,0,0, 
    2,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 1,ndot,bar2, conn,0,0, 
    1,ndot,bar2, conn,0,0, con,0,0,

	1,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 2,ndot,bar2, 1,ndot,bar, conn,0,0, 
    1,ndot,bar2, conn,0,0, 5,ndot,bar2, conn,0,0, 5,ndot,bar, 1,ndot,bar2, conn,0,0, 
    2,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 1,ndot,bar, con,0,0,

	1,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 2,ndot,bar2, 1,ndot,bar, conn,0,0, 
    1,ndot,bar2, conn,0,0, 5,ndot,bar2, conn,0,0, 5,ndot,bar, 1,ndot,bar2, conn,0,0, 
    2,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 1,ndot,bar, con,0,0,


    // dream Another
	1,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 2,ndot,bar2, 1,ndot,bar, conn,0,0, 
    1,ndot,bar2, conn,0,0, 5,ndot,bar2, conn,0,0, 5,ndot,bar, 1,ndot,bar2, conn,0,0, 
    2,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 1,ndot,bar, con,0,0,

	1,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 2,ndot,bar2, 1,ndot,bar, conn,0,0, 
    1,ndot,bar2, conn,0,0, 5,ndot,bar2, conn,0,0, 5,ndot,bar, conn,0,0, 
    1,ndot,bar2, conn,0,0, 2,ndot,bar2, conn,0,0, 1,ndot,bar, conn,0,0, 
    1,ndot,bar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0,


    // now Atlantis
	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, con,0,0,

	6,ddot,bar, conn,0,0, 5,ddot,nbar, conn,0,0, 5,ddot,bar, 0,ndot,bar, 
    1,ndot,bar, conn,0,0, 5,ndot,bar, 5,ndot,bar2, 3,ndot,bar2, con,0,0,

	3,ndot,nbar, 3,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 5,ndot,bar, 5,ndot,bar2,
	3,ndot,bar2, con,0,0,


    // Where 
	3,ndot,nbar, 3,ndot,nbar, 0,ndot,bar, 3,ndot,bar, 3,ndot,bar, 3,ndot,bar, sep,0,0,

	3,ndot,nbar, conn,0,0, 3,ndot,nbar, 0,ndot,bar, 1,ndot,bar, conn,0,0, 
    1,ndot,bar, conn,0,0, 6,ddot,bar2, 4,ndot,bar2, con,0,0,

	4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, 0,ndot,bar, 
    5,ndot,bar, sep,0,0,


    // monster is
	3,ndot,bar, 5,ndot,bar, 3,ndot,bar, conn,0,0, 5,ndot,bar,  3,ndot,bar, conn,0,0, 
    5,ndot,bar, 3,ndot,bar, 2,ndot,bar2, 4,ndot,bar2, con,0,0,

	4,ndot,nbar, conn,0,0, 4,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 
    3,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,


    // I am faded
	0,ndot,nbar, 0,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 
    3,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,



	0,ndot,nbar, 0,ndot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 5,ndot,nbar, sep,0,0,

	0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,bar, 6,ddot,bar, 4,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,
	
	1,ndot,nbar, 1,ndot,nbar, 1,ndot,nbar, 3,ndot,nbar, sep,0,0,


	
	6,ndot,nbar, 6,ndot,nbar, 6,ndot,nbar, 5,ndot,nbar, sep,0,0,
	
	3,ndot,nbar, 3,ndot,nbar, 3,ndot,nbar, 3,ndot,nbar, sep,0,0,
	
	7,ddot,nbar, 7,ddot,nbar, 7,ddot,nbar, 7,ddot,nbar, sep,0,0,

};

int8_t music_script_wish_fill[] = {
	3,ndot,nbar, 6,ddot,bar2, 1,ndot,bar2, 3,ndot,bar2, 5,ndot,bar2, 
	4,ndot,bar, 3,ndot,bar, 2,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,bar, 1,ndot,bar, 2,ndot,bar, 7,ddot,bar, 3,ndot,nbar, 7,ddot,bar,
    sep,0,0,

	1,ndot,nbar,  6,ddot,bar2, 1,ndot,bar2, 3,ndot,bar2, 5,ndot,bar2, 
	4,ndot,bar, 3,ndot,bar, 2,ndot,bar, 1,ndot,bar, sep,0,0,

	7,ddot,nbar, conn,0,0, 7,ddot,nbar, 0,ndot,bar, 3,ddot,bar, 6,ddot,bar,
    7,ddot,bar, sep,0,0,

	
    
    1,ndot,nbar, conn,0,0, 1,ndot,bar, 3,ndot,bar2, 5,ndot,bar2, 4,ndot,nbar,
    conn,0,0, 4,ndot,nbar, sep,0,0,

	0,ndot,bar, 7,ddot,bar, 1,ndot,bar, 2,ndot,bar, 3,ndot,nbar, conn,0,0, 
    3,ndot,nbar, con,0,0,

	3,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 3,ndot,bar, 1,udot,bar, sep,0,0,

	7,ndot,nbar, 5,ndot,nbar, sep,0,0,//这里用的音不准



	6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, 0,ndot,bar, conn,0,0, 
    0,ndot,bar2, 6,ddot,bar2, sep,0,0,

	3,ndot,nbar, 1,ndot,bar2, 2,ndot,bar2, 3,ndot,bar2, 4,ndot,bar2, conn,0,0, 
    4,ndot,nbar, conn,0,0, 4,ndot,bar, 4,ndot,bar2, 3,ndot,bar2, sep,0,0,

	2,ndot,bar, 1,ndot,bar2, 2,ndot,bar2, conn,0,0, 2,ndot,bar, 7,ddot,bar, 
    3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

	0,ndot,nbar, 1,ndot,bar, 3,ndot,bar, 2,ndot,bar, 1,ndot,bar2, 2,ndot,bar2,
	0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,ndot,bar2, sep,0,0,



	2,ndot,bar, 1,ndot,bar2, 2,ndot,bar2, conn,0,0, 2,ndot,bar, 7,ddot,bar, 3,ndot,nbar,
	0,ndot,bar, conn,0,0, 0,ndot,bar2, 6,ddot,bar2, sep,0,0, //在你

	3,ndot,nbar, 1,ndot,bar2, 2,ndot,bar2, 3,ndot,bar2, 4,ndot,bar2, conn,0,0, 
    4,ndot,nbar, conn,0,0, 4,ndot,bar, 4,ndot,bar2, 6,ndot,bar2, sep,0,0,

	5,ndot,bar, 4,ndot,bar, 3,ndot,bar, conn,0,0, 3,ndot,bar2, 2,ndot,bar2, 
    3,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

	0,ndot,nbar, 1,ndot,bar, 3,ndot,bar, 6,ndot,bar, 6,ndot,bar2, 6,ndot,bar2,
    conn,0,0, 6,ndot,bar, 6,ndot,bar, sep,0,0,



	6,ndot,bar, 5,ndot,bar2, 6,ndot,bar2, conn,0,0, 6,ndot,bar, 7,ndot,bar2,
    7,ndot,bar2, conn,0,0, 7,ndot,nbar, 0,ndot,bar2, 3,ndot,bar2, 6,ndot,bar2,
    7,ndot,bar2, sep,0,0,

	1,udot,bar, 3,ndot,bar, 3,ndot,bar, 1,udot,bar, 7,ndot,bar, 3,ndot,bar2,
	5,ndot,bar2, conn,0,0, 5,ndot,nbar, sep,0,0,//而我将。。。人间

	6,ndot,bar, 1,ndot,bar, 1,ndot,bar, 6,ndot,bar, 5,ndot,bar, 4,ndot,bar2,
	3,ndot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 3,ndot,bar2, sep,0,0,

	4,ndot,bar, 5,ndot,bar, 6,ndot,bar, 7,ndot,bar, 7,ndot,bar, 1,udot,bar2,
	1,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,udot,bar2, sep,0,0,



	2,udot,bar, 1,udot,bar2, 2,udot,bar2, 2,udot,bar, 6,ndot,bar2, 7,ndot,bar2,
	7,ndot,nbar, 0,ndot,bar2, 3,ndot,bar2, 6,ndot,bar2, 7,ndot,bar2, sep,0,0,

	1,udot,bar, 3,ndot,bar, 3,ndot,bar, 1,udot,bar, 7,ndot,bar, 3,ndot,bar2,
	5,ndot,bar2, 5,ndot,nbar, sep,0,0,

    6,ndot,bar, 1,ndot,bar, 1,ndot,bar, 6,ndot,bar, 5,ndot,bar, 4,ndot,bar2,
	3,ndot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 3,ndot,bar2, sep,0,0,

	4,ndot,bar, 5,ndot,bar, 6,ndot,bar, 7,ndot,bar, 7,ndot,bar, 1,udot,bar2,
	1,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,udot,bar2, sep,0,0,

    ////////////////////////////

    7,ndot,bar, 1,udot,bar2, 2,udot,bar2, conn,0,0, 2,udot,bar, 7,ndot,bar,
    sep,0,0, //盛世每一天

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, 0,ndot,bar, 
    6,ddot,bar2, 7,ddot,bar2, sep,0,0,

    1,ndot,nbar, 6,ddot,bar2, 1,ndot,bar2, 3,ndot,bar2, 5,ndot,bar2, 5,ndot,bar,
    4,ndot,bar, 4,ndot,bar, 4,ndot,bar2, 3,ndot,bar2, sep,0,0,

    2,ndot,bar2, 1,ndot,bar2, 7,ddot,bar2, 1,ndot,bar2, 2,ndot,bar2, 6,ndot,bar2,
    5,ndot,bar2, 4,ndot,bar2, 3,ndot,nbar, 3,ndot,nbar, sep,0,0,



    4,ndot,nbar, conn,0,0, 4,ndot,nbar, 3,ndot,nbar, 1,ndot,nbar, sep,0,0,

    2,ndot,nbar, 6,ddot,nbar, 7,ddot,nbar, conn,0,0, 7,ddot,bar, 2,ndot,bar,
    sep,0,0,

    1,ndot,nbar, 3,ndot,nbar, 4,ndot,nbar, 3,ndot,bar, 4,ndot,bar, sep,0,0,

    5,ndot,bar, conn,0,0, 5,ndot,bar2, 2,ndot,bar2, conn,0,0, 2, ndot,nbar, 4,ndot,bar, 3,ndot,bar,
    3,ndot,bar, 5,ddot,bar, sep,0,0,



    6,ddot,nbar, conn,0,0, 6,ddot,nbar, conn,0,0, 6,ddot,nbar, 1,ndot,nbar, sep,0,0,

    7,ddot,nbar, 3,ddot,nbar, 6,ddot,nbar, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 
    6,ddot,bar2, sep,0,0,

    6,ndot,bar, 7,ndot,bar, 1,udot,bar, 2,udot,bar, 2,udot,bar2, 3,udot,bar,
    3,udot,bar2, conn,0,0, 3,udot,bar, conn,0,0, 3,udot,bar2, 3,udot,bar2, 
    sep,0,0, //我愿活成

    3,udot,bar, 2,udot,bar2, 4,udot,bar2, conn,0,0, 4,udot,bar, 3,udot,bar, 
    2,udot,bar, 1,udot,bar2, 1,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 
    1,udot,bar2, sep,0,0,



    7,ndot,bar, 1,udot,bar2, 2,udot,bar2, conn,0,0, 2,udot,bar, 7,ndot,bar, 
    sep,0,0, //盛世每一天

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, 0,ndot,bar2, 
    1,udot,bar2, 1,udot,bar2, 7,ndot,bar2, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,bar2, 1,udot,bar2, 1,udot,bar2, 1,udot,bar2,
    7,ndot,nbar, 0,ndot,bar2, 7,ndot,bar2, 7,ndot,bar2, 7,ndot,bar2, sep,0,0,

    1,udot,bar, 3,udot,bar, 3,udot,bar, 1,udot,bar2, conn,0,0, 7,ndot,bar2, 7,ndot,nbar,
    0,ndot,bar2, 1,udot,bar2, 1,udot,bar2, 7,ndot,bar2, sep,0,0,

    

    1,udot,nbar, conn,0,0, 1,udot,bar2, 1,udot,bar2, 1,udot,bar2, 1,udot,bar2, 7,ndot,nbar,
    0,ndot,bar, 1,udot,bar2, 7,ndot,bar2, sep,0,0,

    6,ndot,bar, 7,ndot,bar2, 1,udot,bar2, conn,0,0, 1,udot,bar2, 2,udot,bar, 
    conn,0,0, 7,ndot,bar2, sep,0,0,

    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 
    7,ndot,nbar, sep,0,0,



    modus_change,B_FLAT_MAJOR,0,

    0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,bar2, 3,ndot,bar2, 
    6,ndot,bar2, 7,ndot,bar2,


    //梦你
    1,udot,bar, conn,0,0, 3,ndot,bar, 3,ndot,bar, 1,udot,bar, 7,ndot,bar, 3,ndot,bar2,
    5,ndot,bar2, 5,ndot,nbar, sep,0,0,

    6,ndot,bar, 1,ndot,bar, 1,ndot,bar, 6,ndot,bar, 5,ndot,bar2, 4,ndot,bar,
    3,ndot,bar2, conn,0,0, 3,ndot,nbar, sep,0,0,

    4,ndot,bar, 5,ndot,bar, 6,ndot,bar, 7,ndot,bar, 7,ndot,bar2, 1,udot,bar,
    1,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,udot,bar2, sep,0,0,

    2,udot,bar, 1,udot,bar2, 2,udot,bar2, conn,0,0, 2,udot,bar, 6,ndot,bar2, 
    7,ndot,bar2, conn,0,0, 7,ndot,nbar, 0,ndot,bar2, 3,ndot,bar2, 6,ndot,bar2,
    7,ndot,bar2, sep,0,0,


    // 见你
    1,udot,bar, conn,0,0, 3,ndot,bar, 3,ndot,bar, 1,udot,bar, 7,ndot,bar, 3,ndot,bar2,
    5,ndot,bar2, 5,ndot,nbar, sep,0,0,

    6,ndot,bar, 7,ndot,bar, 1,udot,bar, 2,udot,bar, 2,udot,bar, 3,udot,bar2,
    3,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 3,udot,bar2, sep,0,0,

    3,udot,bar, 2,udot,bar2, 4,udot,bar2, conn,0,0, 4,udot,bar, 3,udot,bar, 2,udot,bar,
    1,udot,bar2, 1,udot,bar2, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,udot,bar2, sep,0,0,

    7,ndot,bar, 1,udot,bar2, 2,udot,bar2, conn,0,0, 2,udot,bar, 7,ndot,bar2, 
    conn,0,0, 6,ndot,bar2,  sep,0,0,


    //边
    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, 0,ndot,bar, 
    conn,0,0, 0,ndot,bar2, 3,udot,bar2, sep,0,0,

    3,udot,bar2, 2,udot,bar, 4,udot,bar2, conn,0,0, 4,udot,bar, 3,udot,bar2, 2,udot,bar2,
    1,udot,bar2, 1,udot,bar, 0,ndot,bar, conn,0,0, 0,ndot,bar2, 1,udot,bar2, sep,0,0,

    7,ndot,bar, 1,udot,bar, 2,udot,bar, 7,udot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 
    6,ndot,nbar, con,0,0,

    6,ndot,bar, 0,ndot,bar, 0,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,
};

int8_t music_script_a_th_year[] = {
    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    4,udot,nbar, conn,0,0, 4,udot,nbar, conn,0,0, 4,udot,nbar, sep,0,0,

    4,udot,nbar, conn,0,0, 4,udot,nbar, conn,0,0, 4,udot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    1,udot,nbar, 7,ndot,nbar, 5,ndot,nbar, sep,0,0,



    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0, //Heart beats

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    3,ndot,bar, 2,ndot,nbar, conn,0,0, 2,ndot,bar, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    5,ndot,nbar, 4,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,



    1,ndot,nbar, conn,0,0, 6,ddot,nbar, 6,ddot,nbar, sep,0,0, // bra

    5,ndot,nbar, 4,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, 3,ndot,nbar, sep,0,0,

    7,ddot,nbar, conn,0,0, 7,ddot,nbar, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,bar, 1,ndot,bar, sep,0,0,

    3,ndot,bar, 2,ndot,nbar, conn,0,0, 2,ndot,bar, 1,ndot,nbar, sep,0,0,



    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0, //stand

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    5,ndot,nbar, 4,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ddot,nbar, conn,0,0, 6,ddot,nbar, conn,0,0, 6,ddot,nbar, sep,0,0,

    5,ndot,nbar, 4,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,bar, 3,ndot,bar, conn,0,0, 3,ndot,nbar, sep,0,0,

    7,ddot,nbar, conn,0,0, 7,ddot,bar, 1,ndot,bar, conn,0,0, 1,ndot,nbar, sep,0,0,



    6,ddot,nbar, conn,0,0, 6,ddot,nbar, conn,0,0, 6,ddot,nbar, sep,0,0, // how

    0,ndot,nbar, conn,0,0, 0,ndot,nbar, conn,0,0, 0,ndot,nbar, sep,0,0,

    6,ddot,nbar, conn,0,0, 6,ddot,nbar, conn,0,0, 6,ddot,nbar, sep,0,0,

    7,ddot,nbar, conn,0,0, 7,ddot,nbar, conn,0,0, 7,ddot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, con,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, sep,0,0,

    0,ndot,nbar, conn,0,0, 0,ndot,nbar, conn,0,0, 0,ndot,nbar, sep,0,0,



    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0, //I have

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, 6,ndot,nbar, 5,ndot,bar, 2,ndot,bar, con,0,0,

    2,ndot,bar, 1,ndot,bar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, 5,ndot,bar, 2,ndot,bar, con,0,0,

    2,ndot,bar, 1,ndot,bar, 1,ndot,nbar, 1,ndot,bar, 2,ndot,bar, sep,0,0,



    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, con,0,0, //thou

    4,ndot,nbar, 3,ndot,nbar, 6,ddot,nbar, con,0,0,

    6,ddot,nbar, conn,0,0, 6,ddot,nbar, 0,ndot,bar, 6,ddot,bar, sep,0,0,

    1,ndot,nbar, 2,ndot,bar, 1,ndot,nbar, 2,ndot,bar, sep,0,0,

    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, sep,0,0,

    3,ndot,nbar, conn,0,0, 3,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

    5,ddot,nbar, conn,0,0, 5,ddot,nbar, conn,0,0, 5,ddot,nbar, con,0,0,
    
    5,ddot,nbar, conn,0,0, 5,ddot,nbar, conn,0,0, 5,ddot,nbar, sep,0,0,



    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0, // more

    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, sep,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, con,0,0,// more

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, 0,ndot,bar, 2,ndot,bar, sep,0,0,

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, 5,ndot,bar, 2,ndot,bar, con,0,0,

    2,ndot,bar, 1,ndot,bar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,

    
    
    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, 1,ndot,bar, sep,0,0, //time

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, 5,ndot,bar, 2,ndot,bar, con,0,0,

    2,ndot,bar, 1,ndot,bar, 1,ndot,nbar, 1,ndot,bar, 2,ndot,bar, sep,0,0,

    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, con,0,0,

    4,ndot,nbar, 3,ndot,nbar, 6,ddot,nbar, con,0,0,

    6,ddot,nbar, conn,0,0, 6,ddot,nbar, 0,ndot,bar, 6,ddot,bar, sep,0,0,

    1,ndot,nbar, 2,ndot,bar, 1,ndot,nbar, 2,ndot,bar, sep,0,0,



    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, sep,0,0, //thou

    3,ndot,nbar, conn,0,0, 3,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,
    
    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, con,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, sep,0,0,



    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    3,udot,nbar, conn,0,0, 3,udot,nbar, conn,0,0, 3,udot,nbar, sep,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    5,ndot,nbar, conn,0,0, 5,ndot,nbar, conn,0,0, 5,ndot,nbar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, sep,0,0,

    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, sep,0,0,

    1,ndot,nbar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0,//one

    

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, sep,0,0, //step

    3,ndot,nbar, conn,0,0, 3,ndot,nbar, conn,0,0, 3,ndot,nbar, con,0,0,
    
    3,ndot,nbar, conn,0,0, 3,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, con,0,0,
    
    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, sep,0,0,

    0,ndot,nbar, conn,0,0, 0,ndot,nbar, conn,0,0, 0,ndot,nbar, sep,0,0,

    0,ndot,nbar, conn,0,0, 0,ndot,nbar, conn,0,0, 0,ndot,nbar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, conn,0,0, 6,ndot,nbar, sep,0,0,



    7,ndot,nbar, conn,0,0, 7,ndot,nbar, conn,0,0, 7,ndot,nbar, sep,0,0, //step

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, con,0,0,

    1,udot,nbar, conn,0,0, 1,udot,nbar, conn,0,0, 1,udot,nbar, sep,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, con,0,0,

    2,udot,nbar, conn,0,0, 2,udot,nbar, conn,0,0, 2,udot,nbar, sep,0,0,

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,// I have died

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,bar, 5,ndot,bar, 2,ndot,bar, con,0,0,



    2,ndot,bar, 1,ndot,bar, conn,0,0, 1,ndot,nbar, conn,0,0, 1,ndot,nbar, sep,0,0, //you

    3,ndot,nbar, 5,ndot,bar, 3,ndot,nbar, conn,0,0, 3,ndot,bar, 1,ndot,bar, sep,0,0,

    3,ndot,nbar, 4,ndot,bar, 3,ndot,nbar, 3,ndot,bar, sep,0,0,

    6,ndot,nbar, conn,0,0, 6,ndot,nbar, 5,ndot,bar, 2,ndot,bar, con,0,0,

    2,ndot,bar, 1,ndot,bar, 1,ndot,nbar, 1,ndot,bar, 2,ndot,bar, sep,0,0,

    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, con,0,0,

    4,ndot,nbar, 3,ndot,nbar, 6,ddot,nbar, con,0,0,

    6,ddot,nbar, conn,0,0, 6,ddot,nbar, 0,ndot,bar, 6,ddot,bar, sep,0,0,



    1,ndot,nbar, 2,ndot,bar, 1,ndot,nbar, 2,ndot,bar, sep,0,0, //love

    4,ndot,nbar, conn,0,0, 4,ndot,nbar, conn,0,0, 4,ndot,nbar, sep,0,0,

    3,ndot,nbar, conn,0,0, 3,ndot,nbar, conn,0,0, 3,ndot,nbar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, con,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, 0,ndot,bar, 2,ndot,bar, sep,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, con,0,0,

    2,ndot,nbar, conn,0,0, 2,ndot,nbar, conn,0,0, 2,ndot,nbar, con,0,0,

    2,ndot,nbar, 0,ndot,nbar, 0,ndot,nbar, sep,0,0,


};