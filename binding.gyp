
{
  	"targets": [
  			{
    	    	"target_name": "bridge",
	    	'include_dirs': ['include', 'include/psat', 'include/calculator/pump', 'include/calculator/motor', 'include/calculator/util',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'bindings/bridge.cpp',
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/pump/').map(f=>'src/calculator/pump/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/motor/').map(f=>'src/calculator/motor/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/util/').map(f=>'src/calculator/util/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/psat/').map(f=>'src/psat/'+f).join(' '))\")",
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
    	    },
		{
	    	"target_name": "phast",
	    	'include_dirs': ['include', 'include/calculator/losses', 'include/phast',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'bindings/phast.cpp',
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/losses/').map(f=>'src/calculator/losses/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/phast/').map(f=>'src/phast/'+f).join(' '))\")",
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
	    },
	    {
	    	"target_name": "psat",
	    	'include_dirs': ['include', 'include/psat', 'include/calculator/pump', 'include/calculator/motor', 'include/calculator/util',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'bindings/psat.cpp',
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/pump/').map(f=>'src/calculator/pump/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/motor/').map(f=>'src/calculator/motor/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/util/').map(f=>'src/calculator/util/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/psat/').map(f=>'src/psat/'+f).join(' '))\")",
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

	    },
	    {
	    	"target_name": "db",
	    	'include_dirs': ['include', 'include/sqlite', 'third_party/sqlite',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
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
