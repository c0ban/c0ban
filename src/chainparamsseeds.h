#ifndef BITCOIN_CHAINPARAMSSEEDS_H
#define BITCOIN_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the bitcoin network
 * AUTOGENERATED by contrib/seeds/generate-seeds.py
 *
 * Each line contains a 16-byte IPv6 address and a port.
 * IPv4 as well as onion addresses are wrapped inside an IPv6 address accordingly.
 */
static SeedSpec6 pnSeed6_main[] = {
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x34,0xc7,0xbf,0xd9}, 3881},	// Tokyo
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x34,0x4e,0x97,0x8a}, 3881}	// Seoul
};

static SeedSpec6 pnSeed6_test[] = {
	  {{0xfe,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xb0,0xbf,0x79,0x0d,0x36,0xc0,0xf3,0x6d}, 13881},
	  {{0xfe,0x80,0x0,0x00,0x00,0x00,0x00,0x00,0xb0,0xf1,0xe5,0xa3,0x72,0xf1,0x72,0xf9}, 13881}
};
#endif // BITCOIN_CHAINPARAMSSEEDS_H
