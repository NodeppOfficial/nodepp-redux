/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_REDUX
#define NODEPP_REDUX

/*────────────────────────────────────────────────────────────────────────────*/

#include <nodepp/optional.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace  nodepp { template< class T > class redux_t {
protected: queue_t<ptr_t<T>> que; ulong mask;

    /*─······································································─*/

    ulong atob( void* object ) const noexcept {
        
        ulong dif = sizeof(ulong) * 8UL - 16UL;
        ulong col = (ulong) object ^ (ulong) &que ;
        ulong row = (ulong) object ^ (ulong) &mask;
        ulong tmp = (ulong) object & 0x0000FFFFFFFFFFFF;
        ulong sum = (col ^ row ^ (col >> 32) ^ (row >> 32)) & 0xFFFF;

        return tmp | ( sum << dif );
    }

    void* btoa( ulong address ) const noexcept { 
        if( que.empty() ){ return nullptr; }

        void* raw = (void*) ( address & 0x0000FFFFFFFFFFFF );
        ulong dif = sizeof(ulong) * 8UL - 16UL;
        
        ulong col = (ulong) raw ^ (ulong) &que ;
        ulong row = (ulong) raw ^ (ulong) &mask;
        ulong sum = (col ^ row ^ (col >> 32) ^ (row >> 32)) & 0xFFFF;

    return ( (address>>dif) != sum ) ? nullptr : raw; }

public: redux_t() {}

    /*─······································································─*/
    // crud - create read update delete

    ulong create() const noexcept {
        que.push( ptr_t<T>() ); return atob( que.last() );
    }

    int remove( ulong address ) const noexcept {
        void* ptr = btoa( address );
        if  ( ptr == nullptr ){ return -1; } 
        que.erase( que.as( ptr ) );
    return 1; }

    ulong update( T value, ulong address ) const noexcept {
        void* ptr = btoa( address );
        if  ( ptr == nullptr ){ return 0; }
        que.as( ptr )->data = type::bind( value ); 
    return address; }

    optional_t<T> read( ulong address ) const noexcept {
        void* ptr = btoa( address );
        if  ( ptr == nullptr ){ return nullptr; }
        auto  raw = que.as( ptr )->data;
        if  ( raw.null() )/**/{ return nullptr; } 
    return *( raw ); }

}; }

#endif

/*────────────────────────────────────────────────────────────────────────────*/
