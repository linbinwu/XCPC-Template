/*
集合容斥
f(S) = \sum_{T \belong S} g(T)
g(S) = \sum_{T \belong S} f(T) * (-1) ^ {|S| - |T|}

Min-Max容斥
max(S) = \sum_{T \belong S} min(T) * (−1) ^ {|T| − 1}
min(S) = \sum_{T \belong S} max(T) * (−1) ^ {|T| − 1}
第k大, 同理有第k小
max_k(S) = \sum_{T \belong S} min(T) * (−1) ^ {|T| − k} * C(|T| - 1, k - 1)
对期望也适用
E[max(S)] = \sum_{T \belong S} E[min(T)] * (−1) ^ {|T| − 1}
*/
