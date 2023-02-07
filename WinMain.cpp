#include "HeaderFiles.h" // header personalizado que deixa o código mais leve e enxuto

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // utilizado como parâmetro na criação da janela, explicado na linha 35
{
	// abaixo será setado qual a reação do programa ao receber as mensagens padrões, todas são definidas pela API do windows, é possível acessár-las ao clicar pressionando ctrl no Visual Studio no nome dos cases. Exemplo: WM_CLOSE
	switch (msg)
	{
		case WM_MOUSEMOVE: // lParam retorna a posição do mouse na tela, 16 maiores bits são a posição Y e os 16 menores são a posição X -> GET_X_PARAM(lParam); para retornar o valor X.
			GET_X_LPARAM(lParam); GET_Y_LPARAM(lParam);
			break; 
		case WM_CHAR: // utilizado para diferenciar input de texto (\n,a,A, ) de outros inputs (que não diferenciam se é upper ou lower/etc) 
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) // wParam é o código que as teclas do teclado retornam sempre que pressionadas, cada uma é mapeada pelo windows, olhe documentação para mais detalhes ->  também é possível usar assim: (wParam == 'A')
				exit(EXIT_SUCCESS); // força saída do programa sempre que a tecla ESC for pressionada
			break;
		case WM_DESTROY: // caso a janela seja fechada
			PostQuitMessage(0); // termina aplicação saindo com o código 0
			break; // desencargo de consciência
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
};
 
int CALLBACK WinMain(
	HINSTANCE hInstance, // identificador da aplicação
	HINSTANCE hPrevInstance, // obsoleto, sempre 0 (era utilizado no windows 16 bits na década de 90 [windows 3.1])
	LPSTR lpCmdLine, // argumentos (argv, argc*)
	int nCmdShow) // modo de exibição da janela (minimizado, maximizado, etc)
{
	// criando janela, é necessário preencher uma "classe"
	LPCWSTR lpClassName = L"D3D"; // nome da classe
	WNDCLASSEX wc = { 0 }; // objeto
	wc.cbSize = sizeof(wc); // passa o tamanho da classe para a API -> não sei o porque
	// seta as flags -> CS_OWNDC = Dá IDs diferentes para cada janela da classe; CS_HREDRAW | CS_VREDRAW -> Redesenha a janela se o usuario alterar o tamanho da janela (não usar com jogos)
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc; // configuração do tipo de controle do IO de mensagens -> DefWindowProc faz com que o windows use o procedimento padrão de tratamento de mensagens do sistema    // -> WndProc para que o controle das mensagens da aplicação seja feito pelo desenvolvedor
	wc.cbClsExtra = 0; // se a classe querem bytes extras (tem algo a ver com a API) -> 0 se não, qualquer outro valor = qnt de bytes
	wc.cbWndExtra = 0; // se as janelas querem bytes extras
	wc.hInstance = hInstance; // identificador da aplicação criado no WinMain
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = lpClassName; // nome da classe, crie uma variável LPCWSTR (char de 2 bytes [long pointer char wide string], não funciona com char* convencional)
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc); // Registra a classe criada, recebe a referência do objeto (variável) da classe

	HWND hWnd = CreateWindowEx
	(
		0,// flags de estilo da janela, 0 é o padrão WS_EX_ACCEPTFILES, é o único útil, mas não para jogos. Possibilita drag-and-drop na janela, se especificado
		lpClassName, // nome da classe que será utilizada para abrir a janela, definido acima
		L"WinAPI", // nome da janela, necessário utilizar a formatação L".." pois é um wide char
		WS_OVERLAPPEDWINDOW, // flags que configuram a janela -> WS_POPUP traz a janela para o primeiro plano e WS_OVERLAPPEDWINDOW é a janela "padrão"
		CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, // tamanho e local em que a janela vai se abrir -> (CW_USEDEFAULT) faz com que o sistema decida onde vai desenhar a janela, (1280,720) é a resolução HD 720p
		nullptr, // identificador da janela pai -> por essa janela não ser "filho", atribui nullptr
		nullptr, // identificador do menu -> por essa janela não ser uma janela "filho" e não ser uma caixa de menu se atribui nullptr
		hInstance, // identificador da aplicação
		nullptr // parâmetros adicionais -> como não há, nullptr

	);
	// se executar o programa nesse ponto, a janela já existe mas ela não é desenhada na tela, só existe o processo em execução
	ShowWindow(hWnd, SW_SHOW); // mostra a janela, os argumentos são o identificador da janela (o ID do processo) e o código para exibir, não é uma flag
	
	// controle das mensagens
	MSG msg; // struct da API, é onde será definido o que acontece com o pressionamento das teclas
	while 
		(GetMessage(
			&msg, // ponteiro/referência para o struct
			NULL, // define quais mensagens serão tratadas
			0, 0) != 0) // se quer filtrar mensagens (seja o primeiro clique do mouse ou a última tecla pressionada, algo do tipo)
			   // se o valor de retorno não for 0, o programa está com problemas
	{
		TranslateMessage(&msg); // traduz as mensagens do teclado/mouse/etc para o sistema operacional -> é função dele decodificar o WM_CHAR
		DispatchMessage(&msg); // envia essas mensagens para que o sistema resolva o que fazer -> DispatchMessage é um define para DispatchMessageW
	}
	return 0;
}
