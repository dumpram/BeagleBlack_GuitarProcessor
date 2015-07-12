kill -9 `ps -eo cmd,pid | grep jackd | cut -d' '  -f5`
