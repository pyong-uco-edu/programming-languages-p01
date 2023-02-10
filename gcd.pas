program example(input,output);
  var x,y,z:integer;
  function gcd(a,b:integer):integer;
  begin{gcd}
    if b=0 then gcd:=a
    else gcd:=gcd(b,a mod b)
  end{gcd};
begin{example}
  readln(x,y);
  write(gcd(x,y))
end{example}.
