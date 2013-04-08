/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __mvdAbstractViewManipulator_h
#define __mvdAbstractViewManipulator_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi2.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtGui>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdTypes.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/** \class AbstractViewManipulator
 *
 *  \brief Base class for QWidget manipulation
 */
class Monteverdi2_EXPORT AbstractViewManipulator :
    public QObject
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public methods.
public:

  /** \brief Constructor. */
  AbstractViewManipulator( QObject* parent =NULL );

  /** \brief Destructor. */
  virtual ~AbstractViewManipulator();

  /** */
  virtual void mouseMoveEvent ( QMouseEvent * event ) = 0;
  virtual void mousePressEvent ( QMouseEvent * event ) = 0;
  virtual void mouseReleaseEvent ( QMouseEvent * event ) = 0;
  virtual void wheelEvent ( QWheelEvent* event) = 0;
  virtual void resizeEvent ( QResizeEvent * event ) = 0;
  virtual void keyPressEvent( QKeyEvent * event )  = 0;

  // TODO: See if HasZoomChanged() pure virtual method can be transformed into Qt signal.
  virtual bool HasZoomChanged() const = 0;

  /** */
  virtual void PropagatePointUnderCursorCoordinates(const QPoint& point);

  /** */
  inline const ImageRegionType& GetViewportImageRegion() const;

  /** */
  inline double GetIsotropicZoom() const;

  /** */
  inline IndexType GetViewportOrigin() const;

  /** */
  void SetSpacing(const SpacingType& spacing);

  /** */
  inline SpacingType GetSpacing() const;

  /** */
  inline SpacingType GetNativeSpacing() const;

  /** */
  void SetOrigin(const PointType& spacing);

  /** */
  inline PointType GetOrigin() const;

  /** */
  inline PointType ScreenIndexToPhysicalPoint(const IndexType & index);
  
  /** */
  inline PointType ScreenIndexToPhysicalPoint(int x, int y);

//
// Public SLOTS.
public slots:
  /** */
  virtual
    void OnModelImageRegionChanged( const ImageRegionType& largestRegion, 
                                    const SpacingType & spacing,
                                    const PointType& )  = 0;
  /** */
  void OnViewportOriginChanged(const IndexType& origin);

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// SIGNALS.
signals:
  /** */
  void PhysicalCursorPositionChanged(double Xpc, double Ypc);

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected types.
protected:
  /** Navigation context  */
  struct NavigationContext
  {
    /**
     * \brief Constructor.
     *
     * Default constructor (safely) initializes POD (Plain Old Data)
     * structure.
     */
    NavigationContext() :
      m_ViewportImageRegion(),
      m_ModelImageRegion(),
      m_SizeXBeforeConstrain(),
      m_SizeYBeforeConstrain()
    {
      // TODO: Initialize default viewport region to (0, 0) i.e. no
      // viewed image.

      ImageRegionType::SizeType region;

      region[ 0 ] = 1;
      region[ 1 ] = 1;

      m_ViewportImageRegion.SetSize( region );
    }

    ImageRegionType m_ViewportImageRegion;
    ImageRegionType m_ModelImageRegion;
    // Stored as double to keep precision when dividing 
    // by scale 
    double m_SizeXBeforeConstrain;
    double m_SizeYBeforeConstrain;
  };

  /** Mouse context */
  struct MouseContext
  {
    /** \brief Default constructor. */
    MouseContext() :
      x( 0 ),
      y( 0 ),
      xMove( 0 ),
      yMove( 0 ),
      moveOriginX(0),
      moveOriginY(0),
      pressed(false)
    {
    }

    int x;  // mousePress x
    int y;  // mousePress y
    int xMove;  // for mouseMove x
    int yMove;  // for mouseMove y
    int moveOriginX; // mouseMove in x (Drag)
    int moveOriginY; // mouseMove in y (Drag)
    bool pressed;
  };

//
// Protected methods.
protected:
  
//
// Protected attributes.
protected:

  /** */
  NavigationContext m_NavigationContext;

  /** */
  MouseContext m_MouseContext;

  /** */
  double       m_IsotropicZoom;

  /** */
  IndexType    m_ViewportOrigin;

  /** */
  SpacingType  m_Spacing;

  /** */
  SpacingType  m_NativeSpacing;
  
  /** */
  PointType    m_Origin;

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:

//
// Private methods.
private:

//
// Private attributes.
private:


  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// SLOTS.
private slots:
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{
/*****************************************************************************/
inline
const ImageRegionType&
AbstractViewManipulator
::GetViewportImageRegion() const
{
  return m_NavigationContext.m_ViewportImageRegion;
}

/*****************************************************************************/
inline 
double
AbstractViewManipulator
::GetIsotropicZoom() const
{
  return m_IsotropicZoom;
}

/*****************************************************************************/
inline 
IndexType
AbstractViewManipulator
::GetViewportOrigin() const
{
  return m_ViewportOrigin;
}

/*****************************************************************************/
inline 
SpacingType
AbstractViewManipulator
::GetSpacing() const
{
  return m_Spacing;
}

/*****************************************************************************/
inline 
SpacingType
AbstractViewManipulator
::GetNativeSpacing() const
{
  return m_NativeSpacing;
}

/*****************************************************************************/
inline 
PointType
AbstractViewManipulator
::GetOrigin() const
{
  return m_Origin;
}

/*****************************************************************************/
inline 
PointType
AbstractViewManipulator
::ScreenIndexToPhysicalPoint(const IndexType & index)
{
  PointType pt;
  // 
  // step #1: screen coordinates -> viewport coordinates
  pt[0] = (double)( index[0] - GetViewportOrigin()[0] ) / GetIsotropicZoom();
  pt[1] = (double)( index[1] - GetViewportOrigin()[1] ) / GetIsotropicZoom();

  //
  // step #2: viewport coordinates -> index
  pt[0] +=  (double)m_NavigationContext.m_ViewportImageRegion.GetIndex()[0];
  pt[1] +=  (double)m_NavigationContext.m_ViewportImageRegion.GetIndex()[1];
  
  //
  // step #3: index -> physical point
  pt[0] = pt[0] * vcl_abs(GetNativeSpacing()[0])  + GetOrigin()[0];
  pt[1] = pt[1] * vcl_abs(GetNativeSpacing()[1])  + GetOrigin()[1];

  return pt;
}

/*****************************************************************************/
inline 
PointType
AbstractViewManipulator
::ScreenIndexToPhysicalPoint(int x, int y)
{
  IndexType index;
  index[0] = (unsigned int)x;
  index[1] = (unsigned int)y;
  
  return ScreenIndexToPhysicalPoint(index);
}

} // end namespace 'mvd'

#endif // __mvdAbstractViewManipulator_h