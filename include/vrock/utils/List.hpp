#pragma once

#include <vector>
#include <array>
#include <deque>
#include <forward_list>
#include <list>

#include <functional>
#include <map>
#include <tuple>
#include <cmath>

namespace vrock::utils {

    template <typename R> constexpr auto less( const R &a, const R &b ) -> bool
    {
        if constexpr ( std::is_floating_point<R>::value )
        {
            if ( std::isnan( b ) )
            {
                if ( std::isnan( a ) )
                {
                    return false;
                }
                return true;
            }
        }
        return a < b;
    }

    template<class T>
    class List : public std::vector<T>
    {
    public:
        List() {}
        List( std::vector<T> v ) : std::vector<T>( v ) {}

        ~List() {}
    public:
        auto inline count() -> size_t
        { 
            return this->size();
        }

        auto inline for_each(std::function<void(T)> exp) -> void
        {
            std::for_each(this->begin(), this->end(), exp);
        }

        template<class R>
        auto inline aggregate(std::function<R (T, R)> exp ) -> R
        {
            R ret = R();
            for_each([&] (T i) {
                ret = exp(i, ret);
            });
            return ret;
        }
        auto inline let( List<T>* l) -> List<T>
        {
            l->resize( this->size( ) );
            std::copy( this->begin( ), this->end( ), l->begin( ) );
            return *this;
        }

        auto inline contains( T val) -> bool
        {
            return any( [ val ]( T it ) { return it == val; } );
        }
        auto inline any() -> bool
        {
            return !this->empty();
        }
        auto inline any( std::function<bool(T)> exp) -> bool
        {
            return std::find_if( this->begin( ), this->end( ), exp ) !=
                this->end( );
        }
        auto inline all( std::function<bool(T)> exp) -> bool
        {
            if (std::find_if_not(this->begin(), this->end(), exp) == this->end())
                return true;
            return false;
        }
        auto inline sequence_equal( List<T> o) -> bool
        {
            return *this == o;
        }

        auto inline concat( List<T> o ) -> List<T>
        {
            this->insert(this->end(), o.begin(), o.end());
            return *this;
        }

        auto inline skip( size_t a ) -> List<T>
        {
            if ( a > this->size( ) )
                return List<T>( );
            return List<T>( std::vector<T>( this->begin( ) + a, this->end( ) ) );
        }
        auto inline skip_while( std::function<bool(T)> exp ) -> List<T>
        {
            auto it = std::find_if_not(this->begin(), this->end(), exp);
            if (it == this->end())
                return List<T>( );
            return List<T>( std::vector<T>( it, this->end() ) );
        }
        auto inline take( size_t a ) -> List<T>
        {
            if ( a > this->size( ) )
                return List<T>( std::vector<T>( this->begin( ), this->end( ) ) );
            return List<T>( std::vector<T>( this->begin( ), this->begin( ) + a ) );
        }
        auto inline take_while( std::function<bool(T)> exp) -> List<T>
        {
            auto it = std::find_if_not(this->begin(), this->end(), exp);
            if ( it == this->end())
                return List<T>( std::vector<T>( this->begin( ), this->end( ) ) );
            return List<T>( std::vector<T>( this->begin(), it ) );
        }
        auto inline revers ( ) -> List<T>
        {
            std::reverse(this->begin(), this->end());
            return *this;
        }

        auto inline first( std::function<bool(T)> exp ) -> T
        {
            auto res = std::find_if(this->begin(), this->end(), exp);
            if (res == this->end())
                throw std::runtime_error("No element matching predicate found");
            return *res;
        }
        auto inline first_or_default( std::function<bool(T)> exp, T _default = T() ) -> T
        {
            auto res = std::find_if(this->begin(), this->end(), exp);
            if (res == this->end())
                return _default;
            return *res;
        }
        auto inline last( std::function<bool(T)> exp ) -> T
        {
            auto res = std::find_if(this->rbegin(), this->rend(), exp);
            if (res == this->rend())
                throw std::runtime_error("No element matching predicate found");
            return *res;
        }
        auto inline last_or_default( std::function<bool(T)> exp, T _default = T() ) -> T
        {
            auto res = std::find_if(this->rbegin(), this->rend(), exp);
            if (res == this->rend())
                return _default;
            return *res;
        }

        auto inline single(std::function<bool(T)> exp) -> T
        {
            auto res1 = std::find_if(this->begin(), this->end(), exp);
            if (res1 == this->end())
                throw std::runtime_error("No element matching predicate found");
            auto res2 = std::find_if(res1 + 1, this->end(), exp);
            if (res2 != this->end())
                throw std::runtime_error("more than one element matching the predicate found");
            return *res1;
        }
        auto inline single_or_default(std::function<bool(T)> exp, T _default = T() ) -> T
        {
            auto res1 = std::find_if(this->begin(), this->end(), exp);
            if (res1 == this->end())
                return _default;
            auto res2 = std::find_if(res1 + 1, this->end(), exp);
            if (res2 != this->end())
                throw std::runtime_error("more than one element matching the predicate found");
            return *res1;
        }

        template<class R> 
        auto inline select( std::function<R(T)> exp ) -> List<R>
        {
            List<R> ret = List<R>( );
            std::for_each( this->begin( ), this->end( ),
                        [ & ]( T i ) { ret.push_back( exp( i ) ); } );
            return ret;
        }
        auto inline where(std::function<bool(T)> exp) -> List<T>
        {
            auto ret = List<T>( );
            std::for_each( this->begin( ), this->end( ),
                        [ & ]( T i )
                        {
                            if ( exp( i ) )
                                ret.push_back( i );
                        } );
            return ret;
        }

        template<class R, class E>
        auto inline join(List<R> o, std::function<bool(T, R)> exp1, std::function<E(T, R)> exp2) -> List<E>
        {
            auto ret = List<E>();
            std::for_each(this->begin(), this->end(), [&](auto i){
                std::for_each(o.begin(), o.end(), [&](auto j) {
                    if (exp1(i, j))
                        ret.push_back(exp2(i, j));
                });
            });
            return ret;
        }

        template <typename... R> 
        auto inline group_by( R... params )
        {
            using key_type = std::tuple<typename remove_pointers<R>::type...>;

            auto comp = make_tuple_less<R...>( );
            auto counter =
                std::map<key_type, std::vector<int>, decltype( comp )>( comp );

            for ( size_t i = 0; i < this->size( ); i++ )
            {
                const auto key = std::make_tuple( ( this->at( i ).*params )... );
                counter[ key ].emplace_back( i );
            }

            auto res = std::map<key_type, List<T>, decltype( comp )>( comp );

            for ( auto &[ key, i ] : counter )
            {
                auto &g = res[ key ];
                g = List<T>( std::vector<T>( i.size( ) ) );
                std::transform( i.begin( ), i.end( ), g.begin( ),
                                [ & ]( auto index ) { return this->at( index ); } );
            }
            return res;
        }

        auto inline order_by( std::function<bool(T,T)> exp ) -> List<T>
        {
            std::sort(this->begin(), this->end(), exp);
            return *this;
        }

        auto inline distinct() -> List<T>
        {
            auto ret = List<T>( );
            std::for_each( this->begin( ), this->end( ),
                        [ & ]( T i )
                        {
                            if ( !ret.contains( i ) )
                                ret.push_back( i );
                        } );
            return ret;
        }
        auto inline union_list(List<T> other) -> List<T>
        {
            return this->concat(other).distinct();
        }
        auto inline intersect(List<T> other) -> List<T>
        {
            auto ret = List<T>( );
            this->for_each([&](T i){
                if (other.contains(i))
                    ret.push_back(i);
            });
            return ret;
        }
        auto inline except(List<T> other) -> List<T>
        {
            auto ret = List<T>( );
            this->for_each([&](T i){
                if (!other.contains(i))
                    ret.push_back(i);
            });
            return ret;
        }
    
        auto inline to_vector() -> std::vector<T>
        {
            return std::vector<T>(this->begin(), this->end());
        }
        auto inline to_deque() -> std::deque<T>
        {
            return std::deque<T>(this->begin(), this->end());
        }
        auto inline to_forward_list() -> std::forward_list<T>
        {
            return std::forward_list<T>(this->begin(), this->end());
        }
        auto inline to_list() -> std::list<T>
        {
            return std::list<T>(this->begin(), this->end());
        }
    private:
        template <class M> struct remove_pointers
        {
            typedef M type;
        };
        template <typename M, typename N> struct remove_pointers<N M::*>
        {
            typedef N type;
        };

        template <size_t i, size_t size, typename... R> struct tuple_less_t
        {
            constexpr static auto tuple_less( const std::tuple<R...> &a,
                                            const std::tuple<R...> &b ) -> bool
            {
                return less( std::get<i>( a ), std::get<i>( b ) ) ||
                    ( !less( std::get<i>( b ), std::get<i>( a ) ) &&
                        tuple_less_t<i + 1, size, R...>::tuple_less( a, b ) );
            }
        };

        template <size_t size, typename... Elements>
        struct tuple_less_t<size, size, Elements...>
        {
            constexpr static auto tuple_less( const std::tuple<Elements...> &a,
                                            const std::tuple<Elements...> &b )
                -> bool
            {
                return false;
            }
        };

        template <typename... R> constexpr auto make_tuple_less( )
        {
            constexpr auto s = sizeof...( R );
            return tuple_less_t<0u, s,
                                typename remove_pointers<R>::type...>::tuple_less;
        }
    };

    template<class T>
    auto select_many(List<List<T>> const &list) -> List<T>
    {
        List<T> flattened;
        for (auto const &l : list)
            flattened.insert(flattened.end(), l.begin(), l.end());
        return flattened;
    }

    template<class T>
    auto select_many(List<std::vector<T>> const &list) -> List<T>
    {
        List<T> flattened;
        for (auto const &v : list)
            flattened.insert(flattened.end(), v.begin(), v.end());
        return flattened;
    }
} // namespace vrock::utils