let rec max_elem_array (lo : int) (hi : int) (arr : int list) : int option =
  let comparison_function (value : int) : bool =
    ((value >= lo) && (value <= hi)) in
  
  let check_value (value : int) : int option =
    if comparison_function value then Some value else None in
  
  let tail_comparison (value : int) (tail : int option) : int option =
    match tail with
    | Some tail_value -> if (value < tail_value) then check_value tail_value else check_value value
    | None -> Some value in
                
    
  match arr with
  | [] -> None
  | [a] -> check_value a 
  | h::t -> (if comparison_function h
             then tail_comparison h (max_elem_array lo hi t)
             else max_elem_array lo hi t)
;;
               
