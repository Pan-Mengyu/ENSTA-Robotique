(define (problem SIGNE-3-0)
(:domain SIGNE)
(:objects A B C)
(:INIT (PosSinge A) (PosCaisse B) (PosBanane C) (Bas) (Handempty) (not (Haut)) (not (HadBanane)))
(:goal (AND (PosSinge C) (Haut) (HadBanane)))
)