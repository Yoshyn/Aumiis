/*
 * debug.hpp
 *
 *  Created on: 25 mai 2011
 *      Author: ANTOINE Sylvestre
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <ctime>

/*! \namespace ami
 * 	Espace de nommage regroupant les outils de Aumiis
 */
namespace ami
{

/**
 * \fn string toString (const Type & value)
 * \brief Fonction renvoyant un std::string correspondant a value.
 * \param value Un flux de la stl
 * \return Un std::string
 */
template <typename Type>
std::string toString (const Type & value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

/**
 * \fn std::ostream & operator << (std::ostream & os, const std::vector<Type> & vect)
 * \brief Fonction permettant de renvoyer un vector dans un ostream.
 *
 * \param os Un flux de la stl
 * \param vect Une instance de vector dont le Type de donnees surcharge l'operateur de Flux
 * \return Le flux
 */
template <typename Type>
std::ostream & operator << (std::ostream & os, const std::vector<Type> & vect)
{
	std::copy(vect.begin(),vect.end(),
			  std::ostream_iterator<Type>(os << " "," "));
	return os;
}

#ifdef AMI_DEBUG

/*! \class  ShowFuncScope
 * 	\brief Classe permetant de voir la portee d'une fonction.
 * 	Il suffit d'utiliser la macro showScopeFunc() définie plus bas au debut	de la fonction.
 */
class ShowFuncScope
{
	std::string m_func;
	clock_t m_beginPeriod;
	static std::string space;
public:
	ShowFuncScope (const std::string & func, const std::string & file, const int & line);

	/**
	 * \fn std::string & spaces ()
	 * \brief Fonction permettant de renvoyer un decalage en espace correspondant a la fonction.
	 * Cela augmente grandement la lisibilité du code.
	 * \return Une chaine de caractere contenant des espaces.
	 */
	static std::string & spaces () { return space; }

	~ShowFuncScope ();
};

/*
 * Note typeid(value).name : N <=> NameSpace, P <=> Pointeur
 */
#define VAR_INFO(value) "[" << (#value) << " = ( (" << (typeid(value).name()) <<")" << ami::toString(value) << " ) ]"
#define VAR_FILE 		"[File=(" << __FILE__ << ")]"
#define VAR_FUNC		"[Func=(" << __func__ << ")]"
#define VAR_LINE 		"[Line=(" << __LINE__ << ")]"

#define debugln(value) 			std::cout << ami::ShowFuncScope::spaces() << VAR_INFO(value) << std::endl;
#define debug(value) 			std::cout << ami::ShowFuncScope::spaces() << VAR_INFO(value) << std::flush;
#define debugAll(value) 		std::cout << ami::ShowFuncScope::spaces() << VAR_INFO(value) << VAR_FUNC << VAR_LINE << VAR_FILE << std::endl;
#define showScopeFunc()			ami::ShowFuncScope tracer(__func__, __FILE__, __LINE__);
#define separator(name)			std::cout << '\n' << ami::ShowFuncScope::spaces() << "<=========================# Separator : " << name << " #=========================>" << '\n' << std::endl;

#else

/*! Affiche [(value)=((Type_de_value) la_valeur_de_value )] et effectue un retour a la ligne si AMI_DEBUG est definie */
#define debugln(value)
/*! Affiche [(value)=((Type_de_value) la_valeur_de_value )] si AMI_DEBUG est definie */
#define debug(value)
/*! Affiche [(value)=((Type_de_value) la_valeur_de_value )], la function, la ligne et le fichier si AMI_DEBUG est definie */
#define debugAll(value)
/*! Affiche la portee d'une function si AMI_DEBUG est definie */
#define showScopeFunc()
/*! Affiche un separateur entre deux blocs de texte si AMI_DEBUG est definie */
#define separator(name)

#endif

} // namespace ami

/*
 * Idees en plus :
 * 	=> Gerer les espacements entre les ShowScopeFunc de maniere a avoir cela :
 * <func1>
 * 		<func2>
 * 		</func2>
 * </func1>
 *
 * 	=> Gerer les espacements entre les ShowScopeFunc et les debug(x) de maniere a avoir cela :
 * <func1>
 * 		<func2>
 * 			[valeur=(uneValeur)]
 * 		</func2>
 * </func1>
 *
 * => Possibilité d'améliorer en sauvegardant dans un fichier ou en affichant en console.
 * 		(Voir : http://cpp.developpez.com/faq/cpp/?page=SL#SL_redirection )
 *
 */

#endif /* DEBUG_HPP_ */
