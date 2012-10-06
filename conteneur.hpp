/*
 * conteneur.hpp
 *
 *  Created on: 27 mai 2011
 *      Author: ANTOINE Sylvestre
 */

#ifndef CONTENEUR_HPP_
#define CONTENEUR_HPP_

#include <assert.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "debug.hpp"

/*! \namespace ami
 * 	Espace de nommage regroupant les outils de Aumiis.
 */
namespace ami
{

/*! \class GridLocation
 * 	\brief Une classe toute simple gerant une paire de uint32_t.
 */
struct GridLocation : public std::pair<uint32_t, uint32_t>
{
	/*! \fn GridLocation (const int & x = 0, const int & y = 0)
	 * \brief Constructeur
	 * \param x Coordonnee x (column)
	 * \param y Coordonnee y (row)
	 */
	GridLocation (const uint32_t & x = 0, const uint32_t & y = 0) :
		pair(x,y)
	{
	}
};

/**
 * \fn std::ostream & operator << (std::ostream & os, const GridLocation & loc)
 * \brief Fonction permettant de renvoyer une GridLocation dans un ostream.
 *
 * \param os Un flux de la STL
 * \param loc Une instance de GridLocation
 * \return Le flux
 */
std::ostream & operator << (std::ostream & os, const GridLocation & loc);

/*! \class Grid
 * 	\brief Une classe gerant une grille de donnees.
 */
template <typename Type>
class Grid
{
	std::vector<Type> m_grid;
	uint32_t m_ColumnCount;
	uint32_t m_RowCount;

public:

	/*! \fn  Grid (const uint32_t&=0, const uint32_t&=0, const Type&=Type())
	 * 	\brief Constructeur.
	 * 	\param rowCount Le nombre de ligne
	 * 	\param columnCount Le nombre de colonne
	 * 	\param defaultValue La valeur par default dont on remplit la grille. Doit avoir un constructeur par default
	 */
	Grid (const uint32_t & rowCount = 0, const uint32_t & columnCount = 0,
		  const Type & defaultValue = Type()) :
		m_grid(rowCount * columnCount,defaultValue),
				m_ColumnCount(columnCount), m_RowCount(rowCount)
	{
	}

	/*! \fn  Grid (const Grid<Type> & grid)
	 * 	\brief Constructeur de recopie.
	 * 	\param grid La grille a copier
	 */
	Grid (const Grid<Type> & grid) :
		m_grid(grid.m_grid), m_ColumnCount(grid.m_ColumnCount),
				m_RowCount(grid.m_RowCount)
	{
	}

	/*! \fn bool contains (const GridLocation&)
	 * 	\brief Fonction permettant de savoir si une GridLocation est dans la grille.
	 * 	\param gl Une coordonnee (GridLocation)
	 * 	\return True si la coordonnee est dans la grille, faux sinon
	 */
	bool contains (const GridLocation & gl) const
	{
		return gl.first < this->m_ColumnCount && gl.second < this->m_RowCount;
	}

	/*! \fn uint32_t getColumnCount ()
	 * 	\brief Fonction permettant de connaitre le nombre de colonnes dans la grille.
	 * 	\return uint32_t
	 */
	uint32_t getColumnCount () const
	{
		return this->m_ColumnCount;
	}

	/*! \fn uint32_t getRowCount ()
	 * 	\brief Fonction permettant de connaitre le nombre de lignes dans la grille.
	 * 	\return uint32_t
	 */
	uint32_t getRowCount () const
	{
		return this->m_RowCount;
	}

	/*! \fn Type& at (const GridLocation&)
	 * 	\brief Fonction permettant d'obtenir une reference sur l'objet de la case correspondant a une GridLocation.
	 * 	Leve un assert de la STL si la GridLocation en parametre n'est pas dans la grille
	 * 	\param gl Une coordonnee (GridLocation)
	 * 	\return Type
	 */
	Type & at (const GridLocation & gl)
	{
		assert(contains(gl));
		return m_grid [gl.second * m_ColumnCount + gl.first];
	}

	/*! \fn Type& at (const GridLocation&)
	 * 	\brief Fonction permettant d'obtenir une reference constante sur l'objet de la case correspondant a une GridLocation.
	 * 	Leve un assert de la STL si la GridLocation en parametre n'est pas dans la grille
	 * 	\param gl Une coordonnee (GridLocation)
	 * 	\return Type
	 */
	const Type & at (const GridLocation & gl) const
	{
		assert(contains(gl));
		return m_grid [gl.second * m_ColumnCount + gl.first];
	}

	/*! \fn Type& operator [] (const GridLocation&)
	 * 	\brief Operateur permettant d'obtenir une reference sur l'objet de la case correspondant a une GridLocation.
	 * 	Attention, ne leve pas d'assert si la GridLocation en parametre n'est pas dans la grille.
	 * 	\param gl Une coordonnee (GridLocation)
	 * 	\return Type
	 */
	Type & operator[] (const GridLocation & gl)
	{
		return m_grid [gl.second * m_ColumnCount + gl.first];
	}

	/*! \fn Type& operator [] (const GridLocation&)
	 * 	\brief Operateur permettant d'obtenir une reference constante sur l'objet de la case correspondant a une GridLocation.
	 * 	Attention, ne leve pas d'assert si la GridLocation en parametre n'est pas dans la grille.
	 * 	\param gl Une coordonnee (GridLocation)
	 * 	\return Type
	 */
	const Type & operator[] (const GridLocation & gl) const
	{
		return m_grid [gl.second * m_ColumnCount + gl.first];
	}

	/*! \fn std::vector<Type> & toVector ()
	 * 	\brief Permet d'obtenir une reference de la grille sous forme de vecteur.
	 * 	\return std::vector<Type>
	 */
	std::vector<Type> & toVector ()
	{
		return m_grid;
	}

	/*! \fn std::vector<Type> & toVector ()
	 * 	\brief Permet d'obtenir une reference constante de la grille sous forme de vecteur.
	 * 	\return std::vector<Type>
	 */
	const std::vector<Type> & toVector () const
	{
		return m_grid;
	}

	/*! \fn std::string toString ()
	 * 	\brief Permet d'obtenir la grille sous forme de chaine de charactere.
	 * 	\return std::string
	 */
	std::string toString () const
	{
		std::ostringstream oss;
		oss << '\n';
		for (uint32_t y = 0; y < m_RowCount; ++y)
		{
			for (uint32_t x = 0; x < m_ColumnCount; ++x)
			{
#ifdef AMI_DEBUG
				oss << ShowFuncScope::spaces() << '[' << std::setw(2)
						<< m_grid [y * m_ColumnCount + x] << "] ";
#else
				oss << '[' << std::setw(2) << m_grid [y * m_ColumnCount + x]
				<< "] ";
#endif
			}
			if (y != m_RowCount - 1)
				oss << '\n';
		}
		return oss.str();
	}
};

/**
 * \fn std::ostream & operator << (std::ostream & os, const Grid<Type> & grid)
 * \brief Fonction permettant de renvoyer une grille dans un ostream.
 *
 * \param os Un flux de la STL
 * \param grid Une instance de Grid dont le Type de donnees surcharge l'operateur de Flux
 * \return Le flux
 */
template <typename Type>
std::ostream & operator << (std::ostream & os, const Grid<Type> & grid)
{
	return os << grid.toString();
}

/*
 * Idees en plus :
 * 	=> Pouvoir redimentionner la grille (Ajouter, supprimer des colonnes).
 *
 * 	=> Obtenir une sous grille.
 *
 *  => Gerer le fait de ne pas utiliser des GridLocations
 */

/*! \class vector
 * 	\brief Une classe toute simple gerant un tableau
 * 	Cette classe n'est pas documentee car elle est deprecated.
 * 	\deprecated {  Use std::vector ! }
 */
template <typename Type>
class vector
{
	Type * m_pointer;
	uint32_t m_size;
	uint32_t m_realSize;

	void release ()
	{
		if (m_pointer)
			delete [] m_pointer;
		m_pointer = NULL;
	}

	void copy (const vector<Type> & vec)
	{
		if (this != &vec)
		{
			m_size = vec.m_size;
			m_realSize = vec.m_realSize;
			m_pointer = new Type [m_realSize];
			for (uint32_t iter = 0; iter < m_size; iter++)
				m_pointer [iter] = vec [iter];
		}
	}

public:
	vector ()
	{
		m_size = 0;
		m_realSize = 10;
		/* Speculation. Le but ici est de ne pas redimentionner le tableau a chaque ajout mais le choix
		 * de 10 n'est pas forcément judicieux.
		 */
		m_pointer = new Type [m_realSize];
	}

	vector (const vector<Type> & vec)
	{
		copy(vec);
	}

	vector<Type> & operator= (const vector<Type> &vec)
	{
		release();
		copy(vec);
		return *this;
	}

	~vector ()
	{
		release();
	}

	void reserve (const uint32_t & realSize)
	{
		m_realSize = realSize;
		Type * tmpPtr = m_pointer;
		m_pointer = new Type [m_realSize];
		for (uint32_t iter = 0; iter < m_size; iter++)
			m_pointer [iter] = tmpPtr [iter];
		delete [] tmpPtr;
	}

	void push_back (const Type & elem)
	{
		if (m_size == m_realSize)
		{
			m_realSize = m_size + 1;
			Type * tmpPtr = m_pointer;
			m_pointer = new Type [m_realSize];

			for (uint32_t iter = 0; iter < m_size; iter++)
				m_pointer [iter] = tmpPtr [iter];
			delete [] tmpPtr;
		}
		m_pointer [m_size] = elem;
		m_size++;
	}

	void pop_back ()
	{
		if (m_size > 0)
			m_size--;
	}

	void flush ()
	{
		release();
		m_size = 0;
		m_realSize = 10;
		m_pointer = new Type [m_realSize];
	}

	bool empty () const
	{
		return m_size == 0;
	}

	uint32_t size () const
	{
		return m_size;
	}

	const Type & operator[] (const uint32_t & indice) const
	{
		//assert(indice < m_size); => Pour les methodes at() les asserts logiquement.
		return m_pointer [indice];
	}

	Type & operator[] (const uint32_t & indice)
	{
		//assert(indice < m_size); => Pour les methodes at() les asserts logiquement.
		return m_pointer [indice];
	}
};

}

#endif /* CONTENEUR_HPP_ */
