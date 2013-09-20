/**
 * @class BasisModel
 * @brief Interface (general, abstract class) represents a basic model (for the MVC-Pattern)
 *
 * It forces the child classes to implement an init()- and an update()-function
 * It's not used in the project yet
 *
 * @author Johanna Wald
 * @version 01
 * @date 20/09/2013 Johanna Wald - start programming
 */

#pragma once

class BasisModel {
public:
	/**
		* @brief abstract, virtual init-function
	*/
	virtual void init() = 0;
	/**
		* @brief abstract, virtual update-function
	*/
	virtual void update() = 0;
};
