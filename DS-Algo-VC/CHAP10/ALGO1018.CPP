void Rearrange(SqList &L, int adr[]) {// �㷨 10.18
  // adr����˳���L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼��
  // ���㷨��adr����L.r��ʹ������
  int i,j,k;
  for (i=1; i<L.length; ++i)
    if (adr[i]!=i) {             // ��iС�ļ�¼δ����λ
      j = i;   L.r[0] = L.r[i];  // �ݴ��¼L.r[i]
      while (adr[j]!=i) { // ����L.r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ
        k = adr[j];   L.r[j] = L.r[k];
        adr[j] = j;   j = k;
      }
      L.r[j] = L.r[0];   adr[j] = j;  // ��¼����λ
    }
} // Rearrange
                             