# Grupa procesu - Wszystkie procesy w pipeline (np. ls -l | sort -k5n | less) mają przydzieloną grupę.
#         Numer grupy jest taki sam jak pid jednego z procesów z tej grupy zwanego liderem grupy.
#         Kernel pozwala na wykonywanie pewnego zbioru działań na grupach, np. można wysłać sygnał do
#         każdego programu w grupie lub uśpić wszystkie procesy w grupie.
# Wyświetlanie:
ps -o pgrp

# Grupa procesów pierwszoplanowych (foreground group) - w danym momencie tylko jedna grupa procesów może
# być pierwszoplanowa. Procesy z tej grupy mogą czytać wejście i wypisywać wyjście z danego terminala.


# Sesja - zbiór grup procesów. Wszystkie procesy w sesji mają ten sam session ID.
ps -o sid

# Bieżąca sesja i terminal - domyślne wywołanie ps zwraca wszystkie procesy związane z bieżącym terminalem i użytkownikiem,
# czyli te należące do bieżącej sesji.
ps

# Identyfikator sesji - session id.

# Terminal sterujący - zazwyczaj sesje mają powiązany ze sobą terminal sterujący.
# Jest to terminal, który został uruchomiony jako pierwszy przez lidera sesji.
# Dana sesja może mieć tylko jeden terminal sterujący.
# Przywódca sesji - proces, który stworzył sesję i jego pid=session ID.
# Przywódca sesji dostaje terminal sterujący przy stworzeniu.
ps -o sid

# Po to jest rozróżnienie na grupy procesów i sesje, żeby np. użytkownik mógł wygodnie zabić całą grupę procesów,
# albo żeby zakończyć sesję niechcianego użytkownika. Albo po to żeby była jakaś hierarchia i porządek.

# Lista wszystkich zadań. Przywódcy sesji to ci dla których sid=pid:
ps -A -o -pid,sid,comm
