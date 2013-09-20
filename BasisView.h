/**
 * @class BasisView
 * @brief Interface (general, abstract class) represents a basic view (for the MVC-Pattern)
 *
 * It forces the child classes to implement an init()- and an draw()-function
 * It's not used in the project yet
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/09/2013 Johanna Wald - start programming
 */

#pragma once


class BasisView {
public:	
	/**
		* @brief init function of the BasisView
		*
		* initialized the BasisView
     	*
	    * @param none
		* @return void
    */
	virtual void init() {};
	/**
		* @brief abstract, general draw function of the BasisView to force the child class to have a draw function 
    */
	virtual void draw() = 0;
};

