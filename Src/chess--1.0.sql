/* Data types */

CREATE OR REPLACE FUNCTION san_in(cstring)
  RETURNS SAN
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE
  AS 'MODULE_PATHNAME';

CREATE OR REPLACE FUNCTION san_out(SAN)
  RETURNS cstring
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE
  AS 'MODULE_PATHNAME';

CREATE OR REPLACE FUNCTION fen_in(cstring)
  RETURNS FEN
  AS 'MODULE_PATHNAME'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OR REPLACE FUNCTION fen_out(FEN)
  RETURNS cstring
  AS 'MODULE_PATHNAME'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE TYPE SAN (
  internallength = 1000,
  input          = san_in,
  output         = san_out
);

CREATE TYPE FEN (
  internallength = 128,
  input = fen_in,
  output = fen_out,
  alignment = double
);

/* Functions */

CREATE FUNCTION get_FirstMoves(SAN, integer)
  RETURNS SAN
  AS 'MODULE_PATHNAME', 'get_FirstMoves'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION has_opening(SAN, SAN)
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'has_opening'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION get_board_state(SAN, integer)
  RETURNS FEN
  AS 'MODULE_PATHNAME', 'get_board_state'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION has_Board(SAN, FEN, integer)
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'has_Board'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;


/* B-tree */

CREATE FUNCTION san_lt(SAN, SAN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'san_lt'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION san_eq(SAN, SAN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'san_eq'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION san_gt(SAN, SAN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'san_gt'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION san_gt_eq(SAN, SAN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'san_gt_eq'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION san_lt_eq(SAN, SAN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'san_lt_eq'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OR REPLACE FUNCTION san_like(SAN, TEXT) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE FUNCTION san_not_like(SAN, TEXT) 
  RETURNS BOOLEAN 
  AS 'MODULE_PATHNAME'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE FUNCTION san_cmp(SAN, SAN)
  RETURNS INTEGER
  AS 'MODULE_PATHNAME', 'san_cmp'
  LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR < (
    LEFTARG = SAN,
    RIGHTARG = SAN,
    PROCEDURE = san_lt,
    COMMUTATOR = >,
    NEGATOR = >=
);

CREATE OPERATOR = (
    LEFTARG = SAN,
    RIGHTARG = SAN,
    PROCEDURE = san_eq,
    COMMUTATOR = =,
    NEGATOR = <>
);

CREATE OPERATOR > (
    LEFTARG = SAN,
    RIGHTARG = SAN,
    PROCEDURE = san_gt,
    COMMUTATOR = <,
    NEGATOR = <=
);

CREATE OPERATOR >= (
  LEFTARG = SAN, 
  RIGHTARG = SAN,
  PROCEDURE = san_gt_eq,
  COMMUTATOR = <=, 
  NEGATOR = <
);

CREATE OPERATOR <= (
  LEFTARG = SAN, 
  RIGHTARG = SAN,
  PROCEDURE = san_lt_eq,
  COMMUTATOR = >=, 
  NEGATOR = >
);

CREATE OPERATOR ~~ (
  LEFTARG = SAN,
  RIGHTARG = TEXT,
  PROCEDURE = san_like,
  COMMUTATOR = !~~
);

CREATE OPERATOR !~~ (
  LEFTARG = SAN,
  RIGHTARG = TEXT,
  PROCEDURE = san_not_like
);

CREATE OPERATOR CLASS san_ops
DEFAULT FOR TYPE SAN USING btree AS
  OPERATOR 1 <,
  OPERATOR 2 <=,
  OPERATOR 3 =,
  OPERATOR 4 >=,
  OPERATOR 5 >,
  FUNCTION 1 san_cmp(SAN, SAN);


/* GIN test */

CREATE OR REPLACE FUNCTION gin_compare(internal, internal) 
  RETURNS internal
  AS 'MODULE_PATHNAME', 'gin_compare'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE OR REPLACE FUNCTION gin_extract_value(internal, internal, internal)
  RETURNS internal 
  AS 'MODULE_PATHNAME', 'gin_extract_value'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE OR REPLACE FUNCTION gin_extract_query(internal, internal, internal, internal, internal, internal, internal)
  RETURNS internal 
  AS 'MODULE_PATHNAME', 'gin_extract_query'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE OR REPLACE FUNCTION gin_consistent(internal, internal, internal, internal, internal, internal, internal, internal)
  RETURNS internal 
  AS 'MODULE_PATHNAME', 'gin_consistent'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE FUNCTION has_board_fn_operator(SAN, FEN)
  RETURNS boolean
  AS 'MODULE_PATHNAME', 'has_board_fn_operator'
  LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION fen_in_san_eq(SAN, FEN) 
  RETURNS BOOLEAN
  AS 'MODULE_PATHNAME', 'fen_in_san_eq'
  LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

CREATE OPERATOR @> (
  LEFTARG = SAN,
  RIGHTARG = FEN,
  PROCEDURE = has_board_fn_operator,
  commutator = '<@',
  restrict = contsel,
  join = contjoinsel
);

CREATE OPERATOR = (
  LEFTARG = SAN,
  RIGHTARG = FEN,
  PROCEDURE = fen_in_san_eq,
  COMMUTATOR = '=',
  NEGATOR = '<>'
);

CREATE OPERATOR CLASS san_gin_ops
DEFAULT FOR TYPE SAN USING gin AS
    OPERATOR 1 @> (SAN, FEN),
    OPERATOR 2 = (SAN, FEN),
    FUNCTION 1 gin_compare(internal, internal),
    FUNCTION 2 gin_extract_value(internal, internal, internal),
    FUNCTION 3 gin_extract_query(internal, internal, internal, internal, internal, internal, internal),
    FUNCTION 4 gin_consistent(internal, internal, internal, internal, internal, internal, internal, internal);