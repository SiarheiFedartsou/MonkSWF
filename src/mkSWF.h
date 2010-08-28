/*
 *  mkSWF.h
 *  MonkSWF
 *
 *  Created by Micah Pearlman on 3/20/09.
 *  Copyright 2009 MP Engineering. All rights reserved.
 *
 */

#ifndef __mkSWF_h__
#define __mkSWF_h__

#include "mkReader.h"
#include "mkHeader.h"
#include "mkTag.h"
#include <map>
#include <vector>
#include <list>
#include <tr1/memory>

using namespace std;

namespace MonkSWF {
	
	class SWF {
	public:

		// factory function prototype
		typedef ITag* (*TagFactoryFunc)( TagHeader* );
	
		SWF() {
			
		}
		
		bool initialize();
		bool read( Reader *reader );
		void print();
		
		void addFactory( uint32_t tag_code, TagFactoryFunc factory ) {
			_tag_factories[ tag_code ] = factory;
		}
		
		TagFactoryFunc getTagFactory( uint32_t tag_code ) {
			TagFactoryMapIter factory = _tag_factories.find( tag_code );
			
			if( factory != _tag_factories.end() && factory->second ) {
				return factory->second;
			}
			
			return 0;
		}
		
		IDefineShapeTag* getShape( uint16_t i ) {		// todo: change to map instead of vector
		
			for ( ShapeDictionaryIter it = _shape_dictionary.begin(); it != _shape_dictionary.end(); it++ ) {
				IDefineShapeTag* shape = *it;
				if( i == shape->shapeId() )
					return shape;
			}
			
			return 0;
		}
		
		
		
//		int32_t numFrames() const {
//			return _frame_list.size();
//		}
		
		Reader* reader() const {
			return _reader;
		}
		void drawFrame( int32_t frame_idx );
		
		
	private:
		typedef std::map< uint32_t, SWF::TagFactoryFunc >	TagFactoryMap;
		typedef TagFactoryMap::iterator						TagFactoryMapIter;
		typedef std::vector< IDefineShapeTag* >				ShapeDictionary;
		typedef ShapeDictionary::iterator					ShapeDictionaryIter;
		typedef std::map< uint16_t, IDefineSpriteTag* >		SpriteDictionary;
//		typedef std::map< uint16_t, IPlaceObjectTag* >		DisplayList;
//		typedef DisplayList::iterator						DisplayListIter;
//		typedef std::vector< DisplayList* >					FrameList;
//		typedef FrameList::iterator							FrameListIter;
		
		
		ShapeDictionary		_shape_dictionary;
		SpriteDictionary	_sprite_dictionary;
		//DisplayList			_display_list;
		//FrameList			_frame_list;
		Header				_header;
		TagFactoryMap		_tag_factories;
		Reader*				_reader;
	
	};
}
#endif // __mkSWF_h__