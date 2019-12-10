/*ALl this occurs after going through the highway
 * Car must recognize exit
 * turn to take exit 
 * recognize if blocked or not
 * if blocked, get back on highway and take next exit 
 * if not blocked 
 */

/* Pseudo Code
 *  
 *  Use integer to check if highway has been taken
 *  If it has, don't run same xases as for taking basic turns
 *  Start checking sonar distance
 *  Use new cases: 
 *    Case 1- If right sensor is triggered 
 *        turning right slowly 
 *    Case 2- If left sensor is triggered 
 *        turning left slowly
 *    Case 3- only center
 *        Drive Straight
 *    
 *   
 *        
 *  If sonar detects object close:
 *    Turn 180 (Using timing mgiht be easiest)
 *    Go straight until right sensor is triggered
 *      Follow that line until back on highway
 *      
 *    
 */
