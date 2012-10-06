/*
 * direction.hpp
 *
 *  Created on: 6 juin 2011
 *      Author: ANTOINE Sylvestre
 */

#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

#include "conteneur.hpp"

/*! \namespace ami
 * 	Espace de nommage regroupant les outils de Aumiis
 */
namespace ami
{

//! Direction.
/*! Represente 4 directions. OTHER et UNDEFINED auront une utilite par la suite (dans le pathFinder). */
enum Direction
{
	UP, 				/*!< Enum value UP pour le haut. */
	LEFT, 				/*!< Enum value LEFT pour la gauche. */
	DOWN, 				/*!< Enum value DOWN pour le bas. */
	RIGHT, 				/*!< Enum value RIGHT pour la droite. */
	DIRECTION_COUNT,	/*!< Enum value DIRECTION_COUNT representant le nombre de directions. */
	OTHER = 0xFE, 		/*!< Enum value OTHER (254) represente une direction connue n'etant pas UP, DOWN, RIGHT ou LEFT. */
	UNDEFINED = 0xFF	/*!< Enum value UNDEFINED (255) represente une direction inconnue. */
};

/*! Represente une GridLocation inconnue (initialise a 255,255) */
const GridLocation UNDEFINED_LOCATION(UNDEFINED,UNDEFINED);

/*! \class  FourDirectionSet
 * 	\brief Classe permettant de representer un systeme a 4 directions.
 */
class FourDirectionSet
{
	static const Direction directions [4];
	static const Direction opposedDirections [4];
	static const Direction leftDirections [4];
	static const Direction rightDirections [4];

public:

	/*! \fn Direction* getDirections ()
	 * 	\brief Fonction permettant de renvoyer un pointeur sur l'ensemble des directions.
	 * 	\return Direction *
	 */
	static const Direction * getDirections ()
	{
		return directions;
	}

	/*! \fn uint8_t getDirectionCount
	 * 	\brief Fonction permettant de renvoyer le nombre de directions.
	 * 	\return uint8_t
	 */
	static uint8_t getDirectionCount ()
	{
		return DIRECTION_COUNT;
	}

	/*! \fn GridLocation getNeighbor (const GridLocation & location, const Direction & direction)
	 * 	\brief Fonction permettant de connaitre le voisin d'une GridLocation en fonction d'une Direction.
	 * 	\param location La GridLocation
	 * 	\param direction La direction
	 * 	\return GridLocation
	 */
	static GridLocation getNeighbor (const GridLocation & location,
									 const Direction & direction)
	{
		switch (direction)
		{
			case UP:
				return GridLocation(location.first,location.second - 1);
			case DOWN:
				return GridLocation(location.first,location.second + 1);
			case LEFT:
				return GridLocation(location.first - 1,location.second);
			case RIGHT:
				return GridLocation(location.first + 1,location.second);
			default:
				break;
		}
		return UNDEFINED_LOCATION;
	}

	/*! \fn Direction getOpposedDirection (const Direction&)
	 * 	\brief Permet de connaitre la direction opposee d'une direction.
	 * 	\param direction La direction
	 * 	\return La direction opposee
	 */
	static Direction getOpposedDirection (const Direction & direction)
	{
		return opposedDirections [direction];
	}

	/*! \fn Direction getLeftDirection (const Direction&)
	 * 	\brief Permet de connaitre la direction gauche d'une direction.
	 * 	\param direction La direction
	 * 	\return La direction gauche
	 */
	static Direction getLeftDirection (const Direction & direction)
	{
		return leftDirections [direction];
	}

	/*! \fn Direction getRightDirection (const Direction&)
	 * 	\brief Permet de connaitre la direction droite d'une direction.
	 * 	\param direction La direction
	 * 	\return La direction droite
	 */
	static Direction getRightDirection (const Direction & direction)
	{
		return rightDirections [direction];
	}
};

/*
 * Idees en plus :
 * 	=> Proposer un code permettant de gerer 8 directions sur la grille.
 * 	(Pour faire propre, cela demande de revoir entièrement le systeme de l'enum)
 */

} // namespace ami


#endif /* DIRECTION_HPP_ */
