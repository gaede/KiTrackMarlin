#ifndef VXDTrack_h
#define VXDTrack_h

#include "IMPL/TrackImpl.h"
#include "IMPL/TrackerHitImpl.h"
#include "EVENT/TrackerHitPlane.h"
#include "EVENT/TrackerHit.h"
#include "MarlinTrk/IMarlinTrkSystem.h"
#include "MarlinTrk/IMarlinTrack.h"

#include <marlin/Global.h>

#include <vector>

#include "ILDImpl/IVXDHit.h"
#include "ILDImpl/IMiniVector.h"
#include "KiTrack/ITrack.h"

#include "Tools/Fitter.h"

// GEAR tools
#include <gear/GEAR.h>
#include <gear/GearParameters.h>
#include <gear/VXDLayerLayout.h>
#include <gear/VXDParameters.h>
#include <gear/BField.h>
#include "gear/gearsurf/MeasurementSurfaceStore.h"
#include "gear/gearsurf/MeasurementSurface.h"
#include "gear/gearsurf/ICoordinateSystem.h"
#include "gear/gearsurf/CartesianCoordinateSystem.h"

//#include "SpacePointBuilder.h"
// CLHEP tools
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Matrix.h"


namespace KiTrackMarlin{


   /** A class for ITracks containing an lcio::Track at core
    */
   class VXDTrack : public ITrack {
      
   public:
      
      /** @param trkSystem An IMarlinTrkSystem, which is needed for fitting of the tracks
       */
      VXDTrack( MarlinTrk::IMarlinTrkSystem* trkSystem );
      
      /** @param hits The hits the track consists of 
       * @param trkSystem An IMarlinTrkSystem, which is needed for fitting of the tracks
       */
      //VXDTrack( std::vector< IVXDHit* > hits , MarlinTrk::IMarlinTrkSystem* trkSystem );
      VXDTrack( std::vector< IMiniVector* > hits , MarlinTrk::IMarlinTrkSystem* trkSystem );
      VXDTrack( const VXDTrack& f );
      VXDTrack & operator= (const VXDTrack & f);
      
      
      /** @return a track in the lcio format
       */
      TrackImpl* getLcioTrack(){ return ( _lcioTrack );}
      
    
      //void addHit( IVXDHit* hit );
      void addHit( IMiniVector* MV );
      
      virtual double getNdf() const { return _lcioTrack->getNdf(); }
      virtual double getChi2() const { return _lcioTrack->getChi2(); }
      virtual double getChi2Prob() const { return _chi2Prob; }

      virtual std::vector< IHit* > getHits() const 
         { std::vector<IHit*> hits; 
         for(unsigned i=0; i<_hits.size();i++) hits.push_back( _hits[i] ); 
         return hits; }
 
      virtual std::vector< IMiniVector* > getMVs() const 
         { std::vector<IMiniVector*> mvhits; 
         for(unsigned i=0; i<_hits.size();i++) mvhits.push_back( _hits[i] ); 
         return mvhits; }
     
      virtual double getQI() const;
      
      
      /** Fits the track and sets chi2, Ndf etc.
       */
      virtual void fit() throw( FitterException );
      
      virtual ~VXDTrack(){ delete _lcioTrack; }
      
   protected:
      
      /** the hits the track consists of
       */
      //std::vector< IVXDHit* > _hits;
      std::vector< IMiniVector* > _hits;     
      
      IMPL::TrackImpl* _lcioTrack;
      
      // for fitting
      MarlinTrk::IMarlinTrkSystem* _trkSystem;
      
      
      double _chi2Prob;

  };
  


}


#endif


