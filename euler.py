def get_prime(maxn):
    primes = []
    isp = [True for i in range(maxn + 1)]
    for i in range(2, maxn + 1):
        if isp[i]:
            primes.append(i)
        for prm in primes:
            if prm * i > maxn:
                break
            isp[prm * i] = False
            if i % prm == 0:
                break
    return primes

print get_prime(89)

