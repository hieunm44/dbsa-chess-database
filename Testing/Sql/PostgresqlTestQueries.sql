create extension chess;

------------------------------------------------------------------------------------------------------------------------
-------------------------------------SAN Data type testing inserting/reading--------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for SAN 'chessgame' data type
CREATE TABLE favorite_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

INSERT INTO favorite_games (id, game_notation) VALUES (1,' 1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. b4 Bxb4 5. c3 Bc5 6. O-O d6 7. d4 exd4 8. cxd4 Bb6 9. Nc3 Na5 10. Bd3 Ne7 11. e5 dxe5 12. dxe5 O-O 13. Qc2 h6 14. Ba3 c5 15. Rad1 Bd7 16. e6 fxe6 17. Bh7+ Kh8 18. Ne5 Nd5 19. Nxd5 exd5 20. Rxd5 Bf5 21. Rxd8 Bxc2 22. Rxf8+ Rxf8 23. Bxc2 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (2, '1. Nf3 Nf6 2. b3 g6 3. Bb2 Bg7 4. g3 d6 5. Bg2 O-O 6. O-O c6 7. d3 e5 8. c4 Ne8 9. Nbd2 f5 10. Qc2 Na6 11. c5 Nxc5 12. Nxe5 Qe7 13. d4 Na6 14. Qc4+ Kh8 15. Nef3 Be6 16. Qc3 f4 17. gxf4 Rxf4 18. Qe3 Rf8 19. Ng5 Nec7 20. Nc4 Rae8 21. Nxe6 Qxe6 22. Qxe6 Rxe6 23. e3 d5 24. Ne5 g5 25. Ba3 Rff6 26. Bh3 Re8 27. Bd7 Rd8 28. Be7 Rxd7 29. Bxf6 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (3, '1. d4 Nf6 2. Nf3 g6 3. Bf4 Bg7 4. e3 d6 5. h3 O-O 6. Nbd2 Nbd7 7. Bc4 c6 8. a4 Re8 9. O-O e5 10. Bh2 e4 11. Ne1 Nf8 12. Qe2 a5 13. c3 b6 14. b4 axb4 15. cxb4 d5 16. Bb3 Ba6 17. Qd1 Bxf1 0-1');
INSERT INTO favorite_games (id, game_notation) VALUES (4, '1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Bd3 Nc6 6. Nxc6 bxc6 7. O-O d5 8. exd5 cxd5 9. Qf3 Bd6 10. Bg5 Be7 11. Nd2 O-O 12. c4 Bb7 13. Bc2 Qb6 14. Qd3 dxc4 15. Qh3 g6 16. Nxc4 Qc6 17. Ne3 Nd5 18. Bxe7 Nxe7 19. Rac1 Qb5 20. Qh4 Nd5 21. Ba4 Qb6 22. Ng4 h5 23. Ne5 Qd6 24. Qg5 Kg7 25. Rfd1 Qd8 26. Qg3 Rh8 27. h4 Qf6 28. Rc4 Rac8 29. Rcd4 Qf5 30. Nc4 Rb8 31. R1d3 Nf6 32. Nd6 Qa5 33. f3 Ba6 34. Rd2 Rb4 35. Bb3 Rxd4 36. Rxd4 Qc5 37. Qf2 Qc1+ 38. Kh2 Qc7 39. Qg3 Qc5 40. Rd2 Qe3 41. Qg5 Qe1 42. Rd1 Qe2 43. Rd2 1/2-1/2');
INSERT INTO favorite_games (id, game_notation) VALUES (5, '1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. Nc3 gxf3 6. O-O d6 7. Qxf3 c6 8. d4 Bh6 9. Bxf7+ Kxf7 10. Qh5+ Kg7 11. Bxf4 Bxf4 12. Rxf4 Nf6 13. Qg5+ Kf7 14. e5 dxe5 15. dxe5 Nd7 16. Ne4 Rg8 17. Qh5+ Kg7 18. exf6+ Kh8 19. Rh4 Nf8 20. Ng5 Rxg5 21. Qxg5 Ne6 22. Qh5 Qg8 23. f7 Qg7 24. Rg4 Qf8 25. Qe5+ Ng7 26. Rxg7 Qxg7 27. f8=Q+ 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (6, '1. e4 e5 2. Nf3 Qf6 3. d4 exd4 4. Bg5 Qg6 5. Bd3 Bc5 6. O-O Ne7 7. Nbd2 O-O 8. Nb3 Bb4 9. a3 Bd6 10. e5 Qe6 11. Nbxd4 Qd5 12. exd6 cxd6 13. Bxe7 Re8 14. Nf5 Nc6 15. Nxd6 Rxe7 16. Bxh7+ Kf8 17. Qxd5 a6 18. Nh4 g6 19. Rae1 b5 20. Rxe7 Kg7 21. Qxf7+ Kh6 22. Qxg6+ 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (7, '1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 O-O 8. c3 d6 9. h3 Na5 10. Bc2 c5 11. d4 Qc7 12. Nbd2 Nc6 13. dxc5 dxc5 14. Nf1 Be6 15. Nh4 g6 16. Qf3 Kh8 17. Bg5 Ng8 18. Qg3 f5 19. f4 Bd6 20. exf5 Bxf5 21. Nxf5 exf4 22. Qf2 gxf5 23. Rad1 Rac8 24. Re6 Be5 25. Qxc5 Qg7 26. Bxf4 Bxf4 27. Rxc6 Bb8 28. Kh1 Ba7 29. Qd6 Bb8 30. Qe6 Rce8 31. Qd7 Re7 32. Qd4 Be5 33. Qd3 Nf6 34. Qxf5 Nd5 35. Rc8 Rf7 36. Rxf8+ Rxf8 37. Qe4 Nf4 38. Re1 Bd6 39. Qd4 Qxd4 40. cxd4 Ne2 41. Bd1 Bb4 42. Bxe2 Bxe1 43. Bf3 Rf4 44. d5 Ra4 45. a3 b4 46. axb4 Rxb4 47. d6 Rxb2 48. d7 Ba5 49. Ne3 Bc7 50. Kg1 a5 51. Bc6 Rb6 52. Ba4 Rb4 53. Bc6 Rd4 54. Nf5 Rc4 55. Bd5 Rc5 56. Be6 Re5 0-1');
INSERT INTO favorite_games (id, game_notation) VALUES (8, '1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3+ 5. bxc3 d6 6. f3 O-O 7. e4 e5 8. Bd3 Nc6 9. Be3 Re8 10. Ne2 b6 11. g4 Na5 12. Ng3 Ba6 13. Qe2 Nd7 14. h4 Nf8 15. f4 exf4 16. Bxf4 Qd7 17. O-O Qa4 18. Nf5 Bxc4 19. Bxc4 Qxc4 20. Qf3 Qe6 21. Rae1 Nc4 22. d5 Qd7 23. Nxg7 Kxg7 24. Bh6+ Kxh6 25. Qf6+ Ng6 26. Rf5 Re5 27. Re2 Rg8 28. Rh5+ Rxh5 29. g5+ Rxg5+ 30. hxg5+ Kh5 31. Rh2+ Kg4 32. Rg2+ 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (9, '1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. O-O Bc5 6. e5 d5 7. exf6 dxc4 8. Re1+ Be6 9. Ng5 Qd5 10. Nc3 Qf5 11. Nce4 Bb6 12. fxg7 Rg8 13. g4 Qg6 14. Nxe6 fxe6 15. Bg5 Rxg7 16. Nf6+ Kf8 17. Qf3 Rf7 18. Rxe6 Qxg5 19. Nxh7+ Kg7 20. Qxf7+ Kxf7 21. Nxg5+ Kg7 22. h4 Rf8 23. Rxc6 1-0');
INSERT INTO favorite_games (id, game_notation) VALUES (10,'1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e6 7. Qd2 Be7 8. O-O-O O-O 9. Nb3 Qb6 10. f3 Rd8 11. h4 d5 12. Bxf6 Bxf6 13. exd5 Bxc3 14. Qxc3 exd5 15. Qc5 Qc7 16. Bb5 Bf5 17. Bxc6 bxc6 18. g4 Be6 19. Nd4 Bd7 20. h5 Qb6 21. Nb3 Qxc5 22. Nxc5 h6 23. Rhe1 Kf8 24. Rd3 Be8 25. Rd4 Rdc8 26. Rf4 a5 27. Re3 Rab8 28. Ra3 Rb5 29. Ne6+ Kg8 30. Nd4 Rb4 31. Rxa5 c5 32. Ne2 d4 33. Rf5 Rcb8 34. b3 c4 35. a3 R4b6 36. Nxd4 cxb3 37. cxb3 Bd7 38. Rf4 Rd6 39. b4 Rd8 40. Kc2 1-0');

select * from favorite_games;

-- Clean up
DROP TABLE favorite_games;
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------




------------------------------------------------------------------------------------------------------------------------
---------------------------------------FEN Data type testing inserting/reading------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for FEN 'chessboard' data type
CREATE TABLE test_chess_board (
    id serial PRIMARY KEY,
    gameboard FEN
);

-- Inserting data
INSERT INTO test_chess_board (gameboard) VALUES ('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1');
INSERT INTO test_chess_board (gameboard) VALUES ('rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2');

-- Read form the table
SELECT * FROM test_chess_board;

-- Clean up
DROP TABLE test_chess_board;
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------





------------------------------------------------------------------------------------------------------------------------
-----------------------------------------has opening functions test-----------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for SAN 'chessgame' data type
CREATE TABLE favorite_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

-- Insert test data
-- Test 1: Basic Matching Opening Moves
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 e5 2. Nf3 Nc6 3. Bb5 a6');
-- Test 2: Non-Matching Opening Moves
INSERT INTO favorite_games (game_notation) VALUES ('1. d4 d5 2. c4 e6');
-- Test 3: Empty String Cases
INSERT INTO favorite_games (game_notation) VALUES ('');
INSERT INTO favorite_games (game_notation) VALUES ('1. e4');
-- and so on for other test cases...

-- Execute tests
-- Test 1: Expect TRUE
SELECT has_opening(
    '1. e4 e5 2. Nf3 Nc6 3. Bb5 a6',
    '1. e4 e5 2. Nf3'
) AS result;

-- Test 2: Expect FALSE
SELECT has_opening(
    '1. Nf2 Nf6 2. c4 g6 3. Nc3 Bg7 4. d4 O-O 5. Bf4 d5 6. Qb3 dxc4',
    '1. Nf3'
) AS result;favorite_games

-- Test 3a: Expect FALSE
SELECT has_opening(
    (SELECT game FROM favorite_games WHERE id = 3),
    '1. e4'
) AS result;

-- Test 3b: Expect FALSE
SELECT has_opening(
    (SELECT game FROM favorite_games WHERE id = 4),
    ''
) AS result;

-- Clean up
DROP TABLE favorite_games;
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------





------------------------------------------------------------------------------------------------------------------------
-----------------------------------------get first moves function test--------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for SAN 'chessgame' data type
CREATE TABLE favorite_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

-- general tests
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 e5 2. Nf3 Nc6 3. Bb5 a6');
INSERT INTO favorite_games (game_notation) VALUES ('1. d4 d5 2. c4 c6');
INSERT INTO favorite_games (game_notation) VALUES ('1. Nf3 Nf6 2. c4 g6');

select *
from favorite_games;

SELECT get_FirstMoves(game_notation, -1) FROM favorite_games WHERE id = 1;

SELECT get_FirstMoves(game_notation, 6) FROM favorite_games WHERE id = 2;


-- more tests *special cases that cover various scenarios, including the presence of comments, annotations, and special
-- moves in the PGN strings.
INSERT INTO favorite_games (game_notation) VALUES ('2. e4 e5 3. Nf3 Nc6 {A comment} 4. Bb5 a6 (A annotation)');
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 {Comment} e5 2. Nf3 Nc6');
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 (Annotation) e5 2. Nf3 Nc6');
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 e5 2. O-O Nc6'); -- Castling
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 d5 2. exd5 Qxd5 {En passant possible next}');
INSERT INTO favorite_games (game_notation) VALUES ('1. e4 e5 {This is a comment} 2. Nf3 Nc6 (Nc3 is also possible) 3. Bb5 a6 4. O-O {Castling} 5. Bxc6 dxc6 6. d4 exd4 (6...Bg4 {Another comment})');


select  * from favorite_games;

SELECT get_FirstMoves(game_notation, 5) FROM favorite_games WHERE id = 1;
SELECT get_FirstMoves(game_notation, 10) FROM favorite_games WHERE id = 7;
-- Expected Result: '1. e4 e5 2. Nf3 Nc6 3. Bb5 '
-- This test checks if the function correctly skips over comments and annotations.

SELECT get_FirstMoves(game_notation, 2) FROM favorite_games WHERE id = 2;
-- Expected Result: '1. e4 e5'
-- This test evaluates how the function handles comments in the middle of moves.

SELECT get_FirstMoves(game_notation, 2) FROM favorite_games WHERE id = 3;
-- Expected Result: '1. e4 e5'
-- This test assesses the handling of annotations within moves.

SELECT get_FirstMoves(game_notation, 3) FROM favorite_games WHERE id = 4;
-- Expected Result: '1. e4 e5 2. O-O'
-- This test ensures that special moves like castling are correctly counted as half-moves.

SELECT get_FirstMoves(game_notation, 4) FROM favorite_games WHERE id = 5;
-- Expected Result: '1. e4 d5 2. exd5 Qxd5'
-- This test checks the handling of moves leading to potential en passant situations.

SELECT get_FirstMoves(game_notation, 9) FROM favorite_games WHERE id = 6;
-- Expected Result: '1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. O-O 5. Bxc6'
-- This result should include the first 10 half-moves, correctly skipping over the comments and annotations,
-- and properly handling the castling notation.

-- Clean up
DROP TABLE favorite_games;
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------





------------------------------------------------------------------------------------------------------------------------
--------------------------------------------get board state function test-----------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for SAN 'chessgame' data type
CREATE TABLE favorite_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

INSERT INTO favorite_games (id, game_notation) VALUES (1,' 1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. b4 Bxb4 5. c3 Bc5 6. O-O d6 7. d4 exd4 8. cxd4 Bb6 9. Nc3 Na5 10. Bd3 Ne7 11. e5 dxe5 12. dxe5 O-O 13. Qc2 h6 14. Ba3 c5 15. Rad1 Bd7 16. e6 fxe6 17. Bh7+ Kh8 18. Ne5 Nd5 19. Nxd5 exd5 20. Rxd5 Bf5 21. Rxd8 Bxc2 22. Rxf8+ Rxf8 23. Bxc2 1-0');

SELECT get_board_state('1. e4 e5 2. Nf3', 0);
-- Expected Result : 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'

SELECT get_board_state('1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. b4 Bxb4 5. c3 Bc5 ', 1);
-- Expected Result : 'rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1'

select get_board_state(game_notation, 2) FROM favorite_games WHERE id = 1;
-- Expected Result : 'rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2'


-- Clean up
DROP TABLE favorite_games;
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------




------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------has board state function test--------------------------------------------
------------------------------------------------------------------------------------------------------------------------

SELECT has_board('Invalid SAN string', 'invalid FEN string', 5);
-- Expected Result :  'failed to parse FEN string: invalid FEN string'

SELECT has_board('1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6', 'rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R b KQkq - 0 5', 10);
-- Expected Result : 'true'

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------




------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------More tests-------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--  Table for SAN 'chessgame' data type
CREATE TABLE test_chess_games (
    id serial PRIMARY KEY,
    game SAN
);

-- Inserting data
INSERT INTO test_chess_games (id, game) VALUES (1,' 1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. b4 Bxb4 5. c3 Bc5 6. O-O d6 7. d4 exd4 8. cxd4 Bb6 9. Nc3 Na5 10. Bd3 Ne7 11. e5 dxe5 12. dxe5 O-O 13. Qc2 h6 14. Ba3 c5 15. Rad1 Bd7 16. e6 fxe6 17. Bh7+ Kh8 18. Ne5 Nd5 19. Nxd5 exd5 20. Rxd5 Bf5 21. Rxd8 Bxc2 22. Rxf8+ Rxf8 23. Bxc2 1-0');
INSERT INTO test_chess_games (id, game) VALUES (2, '1. Nf3 Nf6 2. b3 g6 3. Bb2 Bg7 4. g3 d6 5. Bg2 O-O 6. O-O c6 7. d3 e5 8. c4 Ne8 9. Nbd2 f5 10. Qc2 Na6 11. c5 Nxc5 12. Nxe5 Qe7 13. d4 Na6 14. Qc4+ Kh8 15. Nef3 Be6 16. Qc3 f4 17. gxf4 Rxf4 18. Qe3 Rf8 19. Ng5 Nec7 20. Nc4 Rae8 21. Nxe6 Qxe6 22. Qxe6 Rxe6 23. e3 d5 24. Ne5 g5 25. Ba3 Rff6 26. Bh3 Re8 27. Bd7 Rd8 28. Be7 Rxd7 29. Bxf6 1-0');
INSERT INTO test_chess_games (id, game) VALUES (3, '1. d4 Nf6 2. Nf3 g6 3. Bf4 Bg7 4. e3 d6 5. h3 O-O 6. Nbd2 Nbd7 7. Bc4 c6 8. a4 Re8 9. O-O e5 10. Bh2 e4 11. Ne1 Nf8 12. Qe2 a5 13. c3 b6 14. b4 axb4 15. cxb4 d5 16. Bb3 Ba6 17. Qd1 Bxf1 0-1');
INSERT INTO test_chess_games (id, game) VALUES (4, '1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6 5. Bd3 Nc6 6. Nxc6 bxc6 7. O-O d5 8. exd5 cxd5 9. Qf3 Bd6 10. Bg5 Be7 11. Nd2 O-O 12. c4 Bb7 13. Bc2 Qb6 14. Qd3 dxc4 15. Qh3 g6 16. Nxc4 Qc6 17. Ne3 Nd5 18. Bxe7 Nxe7 19. Rac1 Qb5 20. Qh4 Nd5 21. Ba4 Qb6 22. Ng4 h5 23. Ne5 Qd6 24. Qg5 Kg7 25. Rfd1 Qd8 26. Qg3 Rh8 27. h4 Qf6 28. Rc4 Rac8 29. Rcd4 Qf5 30. Nc4 Rb8 31. R1d3 Nf6 32. Nd6 Qa5 33. f3 Ba6 34. Rd2 Rb4 35. Bb3 Rxd4 36. Rxd4 Qc5 37. Qf2 Qc1+ 38. Kh2 Qc7 39. Qg3 Qc5 40. Rd2 Qe3 41. Qg5 Qe1 42. Rd1 Qe2 43. Rd2 1/2-1/2');
INSERT INTO test_chess_games (id, game) VALUES (5, '1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 g4 5. Nc3 gxf3 6. O-O d6 7. Qxf3 c6 8. d4 Bh6 9. Bxf7+ Kxf7 10. Qh5+ Kg7 11. Bxf4 Bxf4 12. Rxf4 Nf6 13. Qg5+ Kf7 14. e5 dxe5 15. dxe5 Nd7 16. Ne4 Rg8 17. Qh5+ Kg7 18. exf6+ Kh8 19. Rh4 Nf8 20. Ng5 Rxg5 21. Qxg5 Ne6 22. Qh5 Qg8 23. f7 Qg7 24. Rg4 Qf8 25. Qe5+ Ng7 26. Rxg7 Qxg7 27. f8=Q+ 1-0');
INSERT INTO test_chess_games (id, game) VALUES (6, '1. e4 e5 2. Nf3 Qf6 3. d4 exd4 4. Bg5 Qg6 5. Bd3 Bc5 6. O-O Ne7 7. Nbd2 O-O 8. Nb3 Bb4 9. a3 Bd6 10. e5 Qe6 11. Nbxd4 Qd5 12. exd6 cxd6 13. Bxe7 Re8 14. Nf5 Nc6 15. Nxd6 Rxe7 16. Bxh7+ Kf8 17. Qxd5 a6 18. Nh4 g6 19. Rae1 b5 20. Rxe7 Kg7 21. Qxf7+ Kh6 22. Qxg6+ 1-0');
INSERT INTO test_chess_games (id, game) VALUES (7, '1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 O-O 8. c3 d6 9. h3 Na5 10. Bc2 c5 11. d4 Qc7 12. Nbd2 Nc6 13. dxc5 dxc5 14. Nf1 Be6 15. Nh4 g6 16. Qf3 Kh8 17. Bg5 Ng8 18. Qg3 f5 19. f4 Bd6 20. exf5 Bxf5 21. Nxf5 exf4 22. Qf2 gxf5 23. Rad1 Rac8 24. Re6 Be5 25. Qxc5 Qg7 26. Bxf4 Bxf4 27. Rxc6 Bb8 28. Kh1 Ba7 29. Qd6 Bb8 30. Qe6 Rce8 31. Qd7 Re7 32. Qd4 Be5 33. Qd3 Nf6 34. Qxf5 Nd5 35. Rc8 Rf7 36. Rxf8+ Rxf8 37. Qe4 Nf4 38. Re1 Bd6 39. Qd4 Qxd4 40. cxd4 Ne2 41. Bd1 Bb4 42. Bxe2 Bxe1 43. Bf3 Rf4 44. d5 Ra4 45. a3 b4 46. axb4 Rxb4 47. d6 Rxb2 48. d7 Ba5 49. Ne3 Bc7 50. Kg1 a5 51. Bc6 Rb6 52. Ba4 Rb4 53. Bc6 Rd4 54. Nf5 Rc4 55. Bd5 Rc5 56. Be6 Re5 0-1');
INSERT INTO test_chess_games (id, game) VALUES (8, '1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. a3 Bxc3+ 5. bxc3 d6 6. f3 O-O 7. e4 e5 8. Bd3 Nc6 9. Be3 Re8 10. Ne2 b6 11. g4 Na5 12. Ng3 Ba6 13. Qe2 Nd7 14. h4 Nf8 15. f4 exf4 16. Bxf4 Qd7 17. O-O Qa4 18. Nf5 Bxc4 19. Bxc4 Qxc4 20. Qf3 Qe6 21. Rae1 Nc4 22. d5 Qd7 23. Nxg7 Kxg7 24. Bh6+ Kxh6 25. Qf6+ Ng6 26. Rf5 Re5 27. Re2 Rg8 28. Rh5+ Rxh5 29. g5+ Rxg5+ 30. hxg5+ Kh5 31. Rh2+ Kg4 32. Rg2+ 1-0');
INSERT INTO test_chess_games (id, game) VALUES (9, '1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d4 exd4 5. O-O Bc5 6. e5 d5 7. exf6 dxc4 8. Re1+ Be6 9. Ng5 Qd5 10. Nc3 Qf5 11. Nce4 Bb6 12. fxg7 Rg8 13. g4 Qg6 14. Nxe6 fxe6 15. Bg5 Rxg7 16. Nf6+ Kf8 17. Qf3 Rf7 18. Rxe6 Qxg5 19. Nxh7+ Kg7 20. Qxf7+ Kxf7 21. Nxg5+ Kg7 22. h4 Rf8 23. Rxc6 1-0');
INSERT INTO test_chess_games (id, game) VALUES (10,'1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6 6. Bg5 e6 7. Qd2 Be7 8. O-O-O O-O 9. Nb3 Qb6 10. f3 Rd8 11. h4 d5 12. Bxf6 Bxf6 13. exd5 Bxc3 14. Qxc3 exd5 15. Qc5 Qc7 16. Bb5 Bf5 17. Bxc6 bxc6 18. g4 Be6 19. Nd4 Bd7 20. h5 Qb6 21. Nb3 Qxc5 22. Nxc5 h6 23. Rhe1 Kf8 24. Rd3 Be8 25. Rd4 Rdc8 26. Rf4 a5 27. Re3 Rab8 28. Ra3 Rb5 29. Ne6+ Kg8 30. Nd4 Rb4 31. Rxa5 c5 32. Ne2 d4 33. Rf5 Rcb8 34. b3 c4 35. a3 R4b6 36. Nxd4 cxb3 37. cxb3 Bd7 38. Rf4 Rd6 39. b4 Rd8 40. Kc2 1-0');

SELECT count(*)
FROM test_chess_games
WHERE has_board(game,
'rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2', 2);
-- Expected Result : '5'


------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------





------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------B-Tree Index-------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

create extension chess;

CREATE TABLE chess_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

CREATE INDEX game_notation_idx ON chess_games using btree(game_notation san_ops);

-- use python script to generate data /Testing/InternalTesting/PopulateDb.py


-- Specific Opening Move Query test
EXPLAIN ANALYZE
SELECT * FROM chess_games
WHERE has_opening(game_notation, '1. e4 c5 2. Nf3 d6');
-- Activates seq scan.


-- Limited Range Query test
EXPLAIN ANALYZE
SELECT * FROM chess_games
WHERE has_opening(game_notation, '1. d4 d5')
LIMIT 100;
-- Activates seq scan.

-- Ordered Query test
EXPLAIN ANALYZE
SELECT * FROM chess_games
WHERE has_opening(game_notation, '1. c4 e6')
ORDER BY game_notation
LIMIT 50;
-- Activates index scan.

-- Aggregate Queries test
-- need to turn off the seq scan to trigger the index scan
SET enable_seqscan = off;
EXPLAIN ANALYZE
SELECT COUNT(*)
FROM chess_games
WHERE has_opening(game_notation, '1. f4 e5');
SET enable_seqscan = on;

-- Partial Index Query test
EXPLAIN ANALYZE
SELECT * FROM chess_games
WHERE game_notation LIKE '1. Nf3%'
  AND has_opening(game_notation, '1. Nf3 d5');


-- partial index

CREATE INDEX game_notation_idx ON chess_games(game_notation)
WHERE game_notation LIKE '1. Nf3%';

EXPLAIN analyze SELECT * FROM chess_games WHERE game_notation LIKE '1. Nf3%';

SET enable_seqscan = off;
explain analyze SELECT g.game_notation
FROM chess_games g, favorite_games f
WHERE has_opening(g.game_notation, get_firstmoves(f.game_notation, 10));
SET enable_seqscan = on;


------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------





------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------GIN Index----------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

create extension chess;


CREATE TABLE favorite_games (
    id serial PRIMARY KEY,
    game_notation SAN
);

CREATE INDEX idx_chessgame_board_states ON favorite_games USING gin (game_notation san_gin_ops);


SET enable_seqscan = off;
EXPLAIN ANALYZE
SELECT count(*)
FROM favorite_games
WHERE has_board(game_notation, 'r1br2k1/pp2bppp/1qnppn2/6B1/4P3/1NN2P2/PPPQ2PP/2KR1B1R w - - 1 11', 5);

EXPLAIN analyze SELECT * FROM favorite_games
WHERE  has_board(game_notation::san, 'r1br2k1/pp2bppp/1qnppn2/6B1/4P3/1NN2P2/PPPQ2PP/2KR1B1R w - - 1 11'::fen, 5);



select get_board_state('insert a san here', 10)


------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------



