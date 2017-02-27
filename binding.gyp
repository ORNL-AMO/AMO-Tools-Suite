
{
  	"targets": [
		{
	    	"target_name": "bridge",
	    	'include_dirs': ['include', 'include/calculator', 'include/phast', 'include/psat', 'include/sqlite', 'third_party/sqlite',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'src/bindings/bridge.cpp',
				'src/bindings/losses.cpp',
				"<!@(node -e \"console.log(require('fs').readdirSync('src/').map(f=>'src/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/').map(f=>'src/calculator/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/psat/').map(f=>'src/psat/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/phast/').map(f=>'src/phast/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/sqlite/').map(f=>'src/sqlite/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('third_party/sqlite/').map(f=>'third_party/sqlite/'+f).join(' '))\")"
			],
			"conditions": [
		    	[ 'OS=="mac"', {
   		           	"xcode_settings": {
                        'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                        'OTHER_LDFLAGS': ['-stdlib=libc++'],
                        'MACOSX_DEPLOYMENT_TARGET': '10.9',
                        'CLANG_CXX_LIBRARY': 'libc++',
                        'GCC_ENABLE_CPP_RTTI': 'YES',
                        'GCC_ENABLE_CPP_EXCEPTIONS': "YES"
                    },
				}]
	       	]
	    }
	]
}
