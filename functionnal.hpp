/*
 * functionnal.hpp
 *
 *  Created on: 6 juin 2011
 *      Author: ANTOINE Sylvestre
 */

#ifndef FUNCTIONNAL_HPP_
#define FUNCTIONNAL_HPP_

#include <algorithm>
#include <time.h>

#include "conteneur.hpp"
#include "direction.hpp"

/*! \namespace ami
 * 	Espace de nommage regroupant les outils de Aumiis
 */
namespace ami
{

/*! \fn Grid<Type> generateMap (uint32_t column_count, uint32_t row_count , Type init_value, Type init_obstacle, uint32_t nb_obstacle)
 * 	\brief Fonction permettant de generer une grille de donnees aleatoires.
 *  \param column_count Le nombre de colonnes
 *  \param row_count Le nombre de lignes
 *  \param init_value La valeur par defaut a mettre dans la grille. Si non renseignee, c'est le constructeur par defaut de Type qui sera appele
 *  \param init_obstacle La valeur par defaut a mettre dans les obstacles. Si non renseignee, c'est le constructeur par defaut de Type qui sera appele
 *  \param nb_obstacle Le nombre d'obstacles
 * 	\return Instance de Grid
 */
template <typename Type>
Grid<Type> generateMap (uint32_t column_count = 0, uint32_t row_count = 0,
						Type init_value = Type(), Type init_obstacle = Type(),
						uint32_t nb_obstacle = 0)
{
	//Note : Possibilite de faire un random_shuffle directement sur generateMap.toVector()
	showScopeFunc();
	srand(unsigned(time(NULL)));

	Grid<Type> generatedMap(column_count,row_count,init_value);

	std::vector<uint32_t> casesWithObstacle(column_count * row_count);
	for (uint32_t i = 0; i < column_count * row_count; ++i)
		casesWithObstacle [i] = i;

	std::random_shuffle(casesWithObstacle.begin(),casesWithObstacle.end());
	casesWithObstacle.resize(nb_obstacle);

	debugln(casesWithObstacle);

	for (std::vector<uint32_t>::iterator iter = casesWithObstacle.begin(); iter
			!= casesWithObstacle.end(); iter++)
		generatedMap.toVector() [*iter] = init_obstacle;

	debugln(generatedMap);
	return generatedMap;
}

/*! \fn bool pathFinderFourDirectionSet (Grid<Type> & grid, GridLocation & depart, GridLocation & arrive, bool(*traversable) (const Type &))
 * 	\brief Fonction permettant de trouver un chemin dans une grille.
 *  \param grid La grille de donnees.
 *  \param depart La GridLocation de depart
 *  \param arrive La GridLocation d'arrive
 *  \param traversable Fonction de callBack prenant un Type (en reference constante) en parametre et renvoyant un booleen afin de savoir si la case
 *  est traversable ou non
 * 	\return True si un chemin existe, false sinon
 */
template <typename Type>
bool pathFinderFourDirectionSet (Grid<Type> & grid, GridLocation & depart,
								 GridLocation & arrive,
								 bool(*traversable) (const Type &))
{
	showScopeFunc();

	ami::Grid<ami::Direction> path(grid.getRowCount(),grid.getColumnCount(),
								   ami::UNDEFINED);

	path [arrive] = OTHER;
	std::vector<ami::GridLocation> toExplore;
	toExplore.push_back(arrive);

	while (!toExplore.empty() && path [depart] == UNDEFINED)
	{
		ami::GridLocation currentLoc = toExplore.front();
		toExplore.erase(toExplore.begin());

		for (uint8_t i = 0; i < ami::FourDirectionSet::getDirectionCount(); i++)
		{
			GridLocation
					neighbor =
							FourDirectionSet::getNeighbor(
														  currentLoc,
														  FourDirectionSet::getDirections() [i]);

			if (path.contains(neighbor) && path [neighbor] == UNDEFINED
					&& traversable(grid [neighbor]))
			{
				path [neighbor]
						= FourDirectionSet::getOpposedDirection(
																FourDirectionSet::getDirections() [i]);
				toExplore.push_back(neighbor);
			}
		}
	}
	debugln(path);

	return path [depart] != UNDEFINED;
}

/*
 * Idees en plus :
 * 	=> Adapter le pathFinder a une grille a 8 directions.
 *
 * 	=> Rajouter une notion d'heuristique sur les cases a visiter.
 *
 * 	=> Mettre dans une structure l'algorithme afin de pouvoir savoir :
 * 		1) Si il existe un chemin (cela correspond a l'actuel return).
 * 		2) Connaitre la case sur laquelle on va devoir se deplacer au prochain tour.
 * 		3) Pouvoir gerer un choix d'heuristique.
 * 		4) Gerer un labyrinthe de type Thor.
 *
 * 	=> Penser a bien documenter le code de maniere a ce qu'il soit comprehensible!
 */

} // namespace ami

#endif /* FUNCTIONNAL_HPP_ */
