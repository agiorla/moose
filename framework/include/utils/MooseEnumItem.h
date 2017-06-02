/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MOOSEENUMITEM_H
#define MOOSEENUMITEM_H

// STL includes
#include <string>

/**
 * Class for containing MooseEnum item information.
 */
class MooseEnumItem
{
public:
  MooseEnumItem(const std::string & name, const int & id);
  MooseEnumItem(const MooseEnumItem & other);
  MooseEnumItem & operator=(const MooseEnumItem & other);

  ///@{
  /**
   * Return the numeric, name, or raw name.
   */
  const int & id() const { return _id; }
  const std::string & name() const { return _name; }
  const std::string & rawName() const { return _raw_name; }
  ///@}

  ///@{
  /**
   * Operator to allow this class to be used directly as a string for int.
   */
  operator int() const { return _id; }
  operator std::string() const { return _name; }
  ///@}

  ///@{
  /**
   * Comparison operators.
   *
   * The comparison operators using the char * and string are case sensitive.
   */
  bool operator==(const char * value) const;
  bool operator!=(const char * value) const;

  bool operator==(const std::string & value) const;
  bool operator!=(const std::string & value) const;

  bool operator==(int value) const { return _id == value; }
  bool operator!=(int value) const { return _id != value; }

  bool operator==(unsigned short value) const { return _id == value; }
  bool operator!=(unsigned short value) const { return _id != value; }

  bool operator==(const MooseEnumItem & value) const { return _unique == value._unique; }
  bool operator!=(const MooseEnumItem & value) const { return _unique != value._unique; }
  ///@}

  /**
   * Less than operator. This is required for this class to work in maps and sets.
   */
  bool operator<(const MooseEnumItem & other) const { return _unique < other._unique; }

private:
  /// The name as provided in constructor
  std::string _raw_name;

  /// Upper case name
  std::string _name;

  /// The numeric value for item
  int _id;

  /// Unique identifier (hash) created from the id and name combined. This allows items with the
  /// same name but different number and vice versa. It also makes the operator< more robust as well
  /// when storing MooseEnumItem in maps or sets.
  std::size_t _unique;
};

#endif
